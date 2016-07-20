#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <map>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

class Game;

class ResourceManager {

public:

    static ResourceManager* getInstance() {
        if (!_instance) {
            _instance = new ResourceManager();
        }
        return _instance;
    }

    

    void setResourcePath(const std::string);

    void setGame(Game*);

    SDL_Texture* getTexture(const std::string);
    TTF_Font* getFont(const std::string, int);

protected:
    explicit ResourceManager() {}
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:

    using TexturePtr = std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)>;

    std::map<std::string, TexturePtr > _textures;
    std::map<std::string, std::unique_ptr<TTF_Font, void(*)(TTF_Font*)> > _fonts;

    Game* _game;

    std::string _resourcePath;

    static ResourceManager* _instance;

};


#endif
