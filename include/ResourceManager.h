#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <map>
#include <string>
#include <system_error>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Texture.h"
#include "Log.h"

class ResourceManager {

public:

    static ResourceManager* getInstance() {
        if (!_instance) {
            logInstance.log("New Resource Manager");
            _instance = new ResourceManager();
        }
        return _instance;
    }

    SDL_Texture* getTexture(const std::string);
    Texture* getTexture2(const std::string);
    TTF_Font* getFont(const std::string, int);

    void setResourcePath(const std::string);
    void setRenderer(SDL_Renderer*);

    void loadAllResources();
    bool loadTexture(const std::string);
    bool isTextureLoaded(const std::string);
    

protected:
    explicit ResourceManager() {}
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;

private:

    template<typename Creator, typename Destructor, typename... Arguments>
    auto make_resource(Creator c, Destructor d, Arguments&&... args)
    {
        auto r = c(std::forward<Arguments>(args)...);
        if (!r) { throw std::system_error(errno, std::generic_category()); }
        return std::unique_ptr<std::decay_t<decltype(*r)>, decltype(d)>(r, d);
    }

    using FontPtr = std::unique_ptr<TTF_Font, void(*)(TTF_Font*)>;

    std::map<std::string, SDLTexturePtr > _textures;
    std::map<std::string, FontPtr > _fonts;

    std::map<std::string, std::unique_ptr<Texture> > _myTextures;

    SDL_Renderer* _renderer;

    std::string _resourcePath;

    static ResourceManager* _instance;
};


#endif
