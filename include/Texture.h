#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL.h"
#include <string>

using std::string;



class ResourceManager;

class Texture {

public:
    Texture();
    Texture(std::string);

    bool loadTexture(std::string);

    SDL_Texture* getTexture();
    void setTexture(SDL_Texture*);
    void setAlpha(Uint8);

    int getWidth() const;
    int getHeight() const;
    double getRatio() const;

private:

    SDL_Texture* _texture;

    ResourceManager* _resourceManager;

    int _width;
    int _height;
    double _ratio;

};

#endif
