#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <memory>
#include <map>
#include <string>
#include <system_error>
#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Texture.h"
#include "LevelEx.h"
#include "Log.h"

class ResourceManager {

public:

    static ResourceManager* getInstance() {
        if (!instance_) {
            logInstance.log("New Resource Manager");
            instance_ = new ResourceManager();
        }
        return instance_;
    }

    void cleanUp();

    Texture* getTexture(const std::string&);
    TTF_Font* getFont(const std::string&, int);

    void setResourcePath(const std::string&);
    void setRenderer(SDL_Renderer*);

    void loadAllResources();
    bool loadTexture(const std::string&);
    bool isTextureLoaded(const std::string&);
    
    void readAllLevels(const std::string&);
    void loadLevel(int);
    bool isLevelLoaded(int);

    LevelEx getLevel(int);

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

    std::map<std::string, FontPtr > fonts_;

    std::map<std::string, std::unique_ptr<Texture> > myTextures_;

    std::map<int, std::vector<std::string > > rawLevels_;
    std::map<int, LevelEx> levels_;

    SDL_Renderer* renderer_;

    std::string resourcePath_;

    void squareLevel(std::vector<std::vector<Graphics::Block> >&, int);
    void populateFloor(std::vector<std::vector<Graphics::Block> >&, int, int);
    void populateGrass(std::vector<std::vector<Graphics::Block> >&);
    static ResourceManager* instance_;
};


#endif
