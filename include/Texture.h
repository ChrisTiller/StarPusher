#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include "SDL2/SDL.h"

using std::string;
using SDLTexturePtr = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>;

class Texture {

public:

    Texture();
    Texture(SDLTexturePtr);

    SDL_Texture* getTexture() const;
    int getWidth() const;
    int getHeight() const;
    double getRatio() const;

    void setAlpha(Uint8);

private:

    SDLTexturePtr _SDLTexture;

    int _width;
    int _height;
    double _ratio;

};

#endif
