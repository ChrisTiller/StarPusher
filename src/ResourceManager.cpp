#include <iostream>
#include "../include/ResourceManager.h"
#include "../include/Game.h"

ResourceManager* ResourceManager::_instance = NULL;

void ResourceManager::cleanUp() {
    delete _instance;
    _instance = nullptr;
}

void ResourceManager::setResourcePath(const std::string resourcePath) {
    _resourcePath = resourcePath;
}

void ResourceManager::setRenderer(SDL_Renderer* renderer) {
    _renderer = renderer;
}

void ResourceManager::loadAllResources() {
    loadTexture("boy.png");
    loadTexture("catgirl.png");
    loadTexture("cloud_background.png");
    loadTexture("Grass_Block.png");
    loadTexture("Plain_Block.png");
    loadTexture("Wall_Block_Tall.png");
    loadTexture("Wood_Block_Tall.png");
}

TTF_Font* ResourceManager::getFont(const std::string name, int pointSize) {

    auto it = _fonts.find(name);

    if (it == _fonts.end()) {
        
        _fonts.insert(std::make_pair(name, _instance->make_resource(TTF_OpenFont, TTF_CloseFont, (_resourcePath + "/fonts/" + name).c_str(), pointSize)));

        return getFont(name, pointSize);

    }

    return it->second.get();
}

bool ResourceManager::loadTexture(const std::string filePath)
{

    if (filePath == "") 
    {
        return false;
    }

    SDLTexturePtr prt = _instance->make_resource(SDL_CreateTextureFromSurface, SDL_DestroyTexture, _renderer, IMG_Load((_resourcePath + "/images/" + filePath).c_str()));

    if (!prt.get()) 
    {
        //printf(strcat("Unable to load texture: ", filePath.c_str()));
        return false;
    }

    _myTextures.insert(std::make_pair(filePath, std::make_unique<Texture>(std::move(prt))));

    return true;
}

bool ResourceManager::isTextureLoaded(const std::string name)
{
    auto it = _myTextures.find(name);

    return it != _myTextures.end();
}

Texture* ResourceManager::getTexture(const std::string name)
{
    if (!isTextureLoaded(name))
    {
        if (!loadTexture(name))
        {
            return NULL;
        }
    }

    return _myTextures.find(name)->second.get();
}

void ResourceManager::readAllLevels(std::string fileName) {
    std::ifstream levelsFile;

    levelsFile.open(fileName.c_str());

    if (!levelsFile.is_open()){
        return;
    }

    std::string line;
    int levelCounter = 1;

    std::vector<string> rawLevel;

    while (getline(levelsFile, line)) {

        if (line.length() != 0) {
            
            if (line[0] != ';') {
                rawLevel.push_back(line);
            }
            else {

                if (rawLevel.size() != 0) {
                    _rawLevels.insert(std::make_pair(levelCounter, rawLevel));

                    rawLevel.clear();

                    levelCounter++;
                }
                
            }

        }
        else {

            if (rawLevel.size() != 0) {
                _rawLevels.insert(std::make_pair(levelCounter, rawLevel));

                rawLevel.clear();

                levelCounter++;
            }
        }
    }

    levelsFile.close();

    logInstance.log("Levels loaded in Resource Manager");
}

void ResourceManager::loadLevel(int levelNumber) {

    auto it = _rawLevels.find(levelNumber);

    if (it == _rawLevels.end()) {
        return;
    }

    std::vector<string> rawLevel = it->second;

    Graphics::Block character;

    std::vector<Graphics::Block> stars;
    std::vector<Graphics::Block> goals;

    std::vector<std::vector<Graphics::Block> > board;

    int width = 0;
    int height = rawLevel.size();

    std::vector<Graphics::Block> currentRow;

    std::vector<string>::iterator it2;

    int xLocation = 0;
    int yLocation = 0;

    for (it2 = rawLevel.begin(); it2 != rawLevel.end(); it2++) {
        if (it2->length() > width)
        {
            width = it2->length();
        }

        xLocation = 0;

        string::iterator rowIt;

        for (rowIt = it2->begin(); rowIt != it2->end(); rowIt++) {
            
            switch (*rowIt) {
                case ' ':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::NONE, NULL, xLocation, yLocation));
                    break;
                case '#':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::WALL, _instance->getTexture("Wood_Block_Tall.png"), xLocation, yLocation));
                    break;
                case 'G':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::GRASS, _instance->getTexture("Grass_Block.png"), xLocation, yLocation));
                    break;
                case '$':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::NONE, NULL, xLocation, yLocation));
                    stars.push_back(Graphics::Block(Graphics::BlockTypes::STAR, _instance->getTexture("Star.png"), xLocation, yLocation));
                    break;
                case '.':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::NONE, NULL, xLocation, yLocation));
                    goals.push_back(Graphics::Block(Graphics::BlockTypes::GOAL, _instance->getTexture("RedSelector.png"), xLocation, yLocation));
                    break;
                case '*':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::NONE, NULL, xLocation, yLocation));
                    goals.push_back(Graphics::Block(Graphics::BlockTypes::GOAL, _instance->getTexture("Selector.png"), xLocation, yLocation));

                    stars.push_back(Graphics::Block(Graphics::BlockTypes::STAR, _instance->getTexture("Star.png"), xLocation, yLocation));
                    break;
                case '@':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::NONE, NULL, xLocation, yLocation));
                    character = Graphics::Block(Graphics::BlockTypes::PLAYER, _instance->getTexture("boy.png"), xLocation, yLocation);
                    break;
                case '+':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::NONE, NULL, xLocation, yLocation));

                    goals.push_back(Graphics::Block(Graphics::BlockTypes::GOAL, _instance->getTexture("RedSelector.png"), xLocation, yLocation));

                    character = Graphics::Block(Graphics::BlockTypes::PLAYER, _instance->getTexture("boy.png"), xLocation, yLocation);
                    break;
                case 'F':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::NONE, NULL, xLocation, yLocation));
                    break;
            }

            // assume all textures have the same width (which is true for this game at least)
            xLocation += 50;

        }

        board.push_back(currentRow);

        currentRow.clear();

        // assume all textures have the same height (which is true for this game at least)
        yLocation += 40;

    }

    squareLevel(board, width);

    populateFloor(board, character.getLocation().getX() / 50, character.getLocation().getY() / 40);

    populateGrass(board);

    _levels.insert(std::make_pair(levelNumber, LevelEx(board, stars, goals, character, width * 50, height * 40)));

}

void ResourceManager::squareLevel(std::vector<std::vector<Graphics::Block> > &board, int width) {

    int y = 0;

    for (auto &outer : board) {
        while (outer.size() < width) {
            outer.push_back(Graphics::Block(Graphics::BlockTypes::NONE, NULL, outer.size() * 50, y * 40));
        }
        y++;
    }
}

void ResourceManager::populateFloor(std::vector<std::vector<Graphics::Block> > &board, int startX, int startY) {

    if (startX >= board.at(0).size() || startY >= board.size()) {
        return;
    }

    if (startX < 0 || startY < 0) {
        return;
    }

    Graphics::Block existingBlock = board.at(startY).at(startX);

    if (existingBlock.getBlockType() == Graphics::BlockTypes::NONE) {

        board[startY][startX] = Graphics::Block(Graphics::BlockTypes::FLOOR, _instance->getTexture("Plain_Block.png"), existingBlock.getLocation());

        populateFloor(board, startX - 1, startY);
        populateFloor(board, startX, startY - 1);
        populateFloor(board, startX + 1, startY);
        populateFloor(board, startX, startY + 1);

    }
    
}

void ResourceManager::populateGrass(std::vector<std::vector<Graphics::Block> > &board) {

    for (auto &outer : board) {

        for (auto &inner : outer) {
            if (inner.getBlockType() == Graphics::BlockTypes::NONE) {
                inner = Graphics::Block(Graphics::BlockTypes::FLOOR, _instance->getTexture("Grass_Block.png"), inner.getLocation());
            }
        }

    }

}

bool ResourceManager::isLevelLoaded(int levelNumber){
    auto it = _levels.find(levelNumber);

    return it != _levels.end();
}

LevelEx ResourceManager::getLevel(int levelNumber) {
    
    if (!isLevelLoaded(levelNumber))
    {
        loadLevel(levelNumber);
    }

    return _levels.find(levelNumber)->second;
}