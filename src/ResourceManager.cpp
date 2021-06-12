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

SDL_Texture* ResourceManager::getTexture(const std::string name) {

    auto it = _textures.find(name);

    if (it == _textures.end()) {

        _textures.insert(std::make_pair(name, _instance->make_resource(SDL_CreateTextureFromSurface, SDL_DestroyTexture, _renderer, IMG_Load((_resourcePath + "/images/" + name).c_str()))));

        return getTexture(name);

    }

    return it->second.get();

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
    if (_myTextures.empty())
    {
        return false;
    }

    auto it = _myTextures.find(name);

    return it != _myTextures.end();
}

Texture* ResourceManager::getTexture2(const std::string name)
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
