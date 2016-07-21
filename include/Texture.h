#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL.h"
#include <string>

using std::string;

enum TEXTURE_TYPE {
    WALL,
    STAR,
    PLAYER,
    OFFGOAL,
    ONGOAL,
    FLOOR,
    GRASS,
    NONE
};

class ResourceManager;

class Texture {

public:
    Texture();
    Texture(std::string);

    bool loadTexture(std::string);

    SDL_Texture* getTexture() const;
    TEXTURE_TYPE getTextureType() const;
    void setAlpha(Uint8);

    void setTextureType(TEXTURE_TYPE);

    int getWidth() const;
    int getHeight() const;
    double getRatio() const;

private:

    SDL_Texture* _texture;
    
    ResourceManager* _resourceManager;

    int _width;
    int _height;
    double _ratio;

    TEXTURE_TYPE _type;

};

#endif