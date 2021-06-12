#include <iostream>
#include "../include/ResourceManager.h"
#include "../include/Game.h"

ResourceManager* ResourceManager::_instance = NULL;

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
        printf(strcat("Unable to load texture: ", filePath.c_str()));
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

    vector<string> rawLevel;

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

}

bool ResourceManager::isLevelLoaded(int levelNumber){
    auto it = _rawLevels.find(levelNumber);

    return it != _rawLevels.end();
}

LevelEx ResourceManager::getLevel(int levelNumber) {
    
    if (!isLevelLoaded(levelNumber))
    {
        loadLevel(levelNumber);
    }

    return _levels.find(levelNumber)->second;
}