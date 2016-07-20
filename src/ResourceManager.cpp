#include "../include/ResourceManager.h"
#include "../include/Game.h"

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

        TexturePtr newTexture = std::make_unique<TexturePtr>(SDL_CreateTextureFromSurface(_game->getWindowPtr()->getRenderer(), IMG_Load((_resourcePath + "/images/" + name).c_str())), SDL_DestroyTexture);

        //_textures.insert(std::make_pair(name, newTexture));

        return newTexture.get();

    }

    return it->second.get();

}


TTF_Font* ResourceManager::getFont(const std::string name, int pointSize) {

    /*auto it = _fonts.find(name);

    if (it == _fonts.end()) {

        std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> newFont = std::unique_ptr<TTF_Font, void(*)(TTF_Font*)>(TTF_OpenFont((_resourcePath + "/fonts/" + name).c_str(), pointSize), TTF_CloseFont);

        _fonts.insert(std::make_pair(name, newFont));

        return newFont->get();

    }

    return it->second->get();*/
    return NULL;
}
