#include "../include/ResourceManager.h"
#include "../include/Game.h"
#include <iostream>

ResourceManager* ResourceManager::_instance = NULL;

void ResourceManager::setResourcePath(const std::string resourcePath) {
    _resourcePath = resourcePath;
}

void ResourceManager::setGame(Game* game) {
    _game = game;
}

SDL_Texture* ResourceManager::getTexture(const std::string name) {

    auto it = _textures.find(name);

    if (it == _textures.end()) {

        _textures.insert(std::make_pair(name, _instance->make_resource(SDL_CreateTextureFromSurface, SDL_DestroyTexture, _game->getWindowPtr()->getRenderer(), IMG_Load((_resourcePath + "/images/" + name).c_str()))));

        return getTexture(name);

    }

    return it->second.get();

}


TTF_Font* ResourceManager::getFont(const std::string name, int pointSize) {

    auto it = _fonts.find(name);

    if (it == _fonts.end()) {

        FontPtr newFont = std::unique_ptr<TTF_Font, void(*)(TTF_Font*)>(TTF_OpenFont((_resourcePath + "/fonts/" + name).c_str(), pointSize), TTF_CloseFont);

        _fonts.insert(std::make_pair(name, std::move(newFont)));

        return getFont(name, pointSize);

    }

    return it->second.get();
}
