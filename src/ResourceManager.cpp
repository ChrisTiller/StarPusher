#include <iostream>
#include "../include/ResourceManager.h"
#include "../include/Game.h"

ResourceManager* ResourceManager::instance_ = NULL;

void ResourceManager::cleanUp() {
    delete instance_;
    instance_ = nullptr;
}

void ResourceManager::setResourcePath(const std::string &resourcePath) {
    resourcePath_ = resourcePath;
}

void ResourceManager::setRenderer(SDL_Renderer* renderer) {
    renderer_ = renderer;
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

TTF_Font* ResourceManager::getFont(const std::string &name, int pointSize) {

    auto it = fonts_.find(name);

    if (it == fonts_.end()) {
        
        fonts_.insert(std::make_pair(name, instance_->make_resource(TTF_OpenFont, TTF_CloseFont, (resourcePath_ + "/fonts/" + name).c_str(), pointSize)));

        return getFont(name, pointSize);

    }

    return it->second.get();
}

bool ResourceManager::loadTexture(const std::string &filePath)
{

    if (filePath == "") 
    {
        return false;
    }

    SDLTexturePtr prt = instance_->make_resource(SDL_CreateTextureFromSurface, SDL_DestroyTexture, renderer_, IMG_Load((resourcePath_ + "/images/" + filePath).c_str()));

    if (!prt.get()) 
    {
        //printf(strcat("Unable to load texture: ", filePath.c_str()));
        return false;
    }

    myTextures_.insert(std::make_pair(filePath, std::make_unique<Texture>(std::move(prt))));

    return true;
}

bool ResourceManager::isTextureLoaded(const std::string &name)
{
    auto it = myTextures_.find(name);

    return it != myTextures_.end();
}

Texture* ResourceManager::getTexture(const std::string &name)
{
    if (!isTextureLoaded(name))
    {
        if (!loadTexture(name))
        {
            return NULL;
        }
    }

    return myTextures_.find(name)->second.get();
}

void ResourceManager::readAllLevels(const std::string &fileName) {
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
                    rawLevels_.insert(std::make_pair(levelCounter, rawLevel));

                    rawLevel.clear();

                    levelCounter++;
                }
                
            }

        }
        else {

            if (rawLevel.size() != 0) {
                rawLevels_.insert(std::make_pair(levelCounter, rawLevel));

                rawLevel.clear();

                levelCounter++;
            }
        }
    }

    levelsFile.close();

    logInstance.log("Levels loaded in Resource Manager");
}

void ResourceManager::loadLevel(int levelNumber) {

    auto it = rawLevels_.find(levelNumber);

    if (it == rawLevels_.end()) {
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

    int xLocation = 0;
    int yLocation = 0;

    for (auto &row : rawLevel) {
        if (row.length() > width)
        {
            width = row.length();
        }

        xLocation = 0;

        for (auto &cell : row) {
            
            switch (cell) {
                case ' ':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::kNone, NULL, xLocation, yLocation));
                    break;
                case '#':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::kWall, instance_->getTexture("Wood_Block_Tall.png"), xLocation, yLocation));
                    break;
                case 'G':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::kGrass, instance_->getTexture("Grass_Block.png"), xLocation, yLocation));
                    break;
                case '$':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::kNone, NULL, xLocation, yLocation));
                    stars.push_back(Graphics::Block(Graphics::BlockTypes::kStar, instance_->getTexture("Star.png"), xLocation, yLocation));
                    break;
                case '.':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::kNone, NULL, xLocation, yLocation));
                    goals.push_back(Graphics::Block(Graphics::BlockTypes::kGoal, instance_->getTexture("RedSelector.png"), xLocation, yLocation));
                    break;
                case '*':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::kNone, NULL, xLocation, yLocation));
                    goals.push_back(Graphics::Block(Graphics::BlockTypes::kGoal, instance_->getTexture("Selector.png"), xLocation, yLocation));

                    stars.push_back(Graphics::Block(Graphics::BlockTypes::kStar, instance_->getTexture("Star.png"), xLocation, yLocation));
                    break;
                case '@':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::kNone, NULL, xLocation, yLocation));
                    character = Graphics::Block(Graphics::BlockTypes::kPlayer, instance_->getTexture("boy.png"), xLocation, yLocation);
                    break;
                case '+':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::kNone, NULL, xLocation, yLocation));

                    goals.push_back(Graphics::Block(Graphics::BlockTypes::kGoal, instance_->getTexture("RedSelector.png"), xLocation, yLocation));

                    character = Graphics::Block(Graphics::BlockTypes::kPlayer, instance_->getTexture("boy.png"), xLocation, yLocation);
                    break;
                case 'F':
                    currentRow.push_back(Graphics::Block(Graphics::BlockTypes::kNone, NULL, xLocation, yLocation));
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

    populateFloor(board, character.getLocation().x / 50, character.getLocation().y / 40);

    populateGrass(board);

    levels_.insert(std::make_pair(levelNumber, LevelEx(board, stars, goals, character, width * 50, height * 40)));

}

void ResourceManager::squareLevel(std::vector<std::vector<Graphics::Block> > &board, int width) {

    int y = 0;

    for (auto &outer : board) {
        while (outer.size() < width) {
            outer.push_back(Graphics::Block(Graphics::BlockTypes::kNone, NULL, outer.size() * 50, y * 40));
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

    if (existingBlock.getBlockType() == Graphics::BlockTypes::kNone) {

        board[startY][startX] = Graphics::Block(Graphics::BlockTypes::kFloor, instance_->getTexture("Plain_Block.png"), existingBlock.getLocation());

        populateFloor(board, startX - 1, startY);
        populateFloor(board, startX, startY - 1);
        populateFloor(board, startX + 1, startY);
        populateFloor(board, startX, startY + 1);

    }
    
}

void ResourceManager::populateGrass(std::vector<std::vector<Graphics::Block> > &board) {

    for (auto &outer : board) {

        for (auto &inner : outer) {
            if (inner.getBlockType() == Graphics::BlockTypes::kNone) {
                inner = Graphics::Block(Graphics::BlockTypes::kFloor, instance_->getTexture("Grass_Block.png"), inner.getLocation());
            }
        }

    }

}

bool ResourceManager::isLevelLoaded(int levelNumber){
    auto it = levels_.find(levelNumber);

    return it != levels_.end();
}

LevelEx ResourceManager::getLevel(int levelNumber) {
    
    if (!isLevelLoaded(levelNumber))
    {
        loadLevel(levelNumber);
    }

    return levels_.find(levelNumber)->second;
}
