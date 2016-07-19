#ifndef TEXTURE_H
#define TEXTURE_H

#include "SDL2/SDL.h"
#include <string>

using std::string;

class Texture {

public:
    Texture();
    Texture(std::string, SDL_Renderer*);
    ~Texture();

    bool loadTexture(std::string, SDL_Renderer*);

    SDL_Texture* getTexture() const;
    void setAlpha(Uint8);

    int getWidth() const;
    int getHeight() const;
    double getRatio() const;

    void deleteTexture();

private:

    SDL_Texture* _texture;
    
    int _width;
    int _height;
    double _ratio;

};

#endif