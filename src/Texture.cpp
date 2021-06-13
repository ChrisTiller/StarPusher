#include "SDL2/SDL_image.h"
#include "../include/Texture.h"
#include "../include/Log.h"

Texture::Texture() : _SDLTexture{nullptr, nullptr}
{
    _width = 0;
    _height = 0;
    _ratio = 0;
}

Texture::Texture(SDLTexturePtr texture) : _SDLTexture{nullptr, nullptr}
{
    _SDLTexture = std::move(texture);

    if (_SDLTexture.get())
    {
        SDL_QueryTexture(_SDLTexture.get(), NULL, NULL, &_width, &_height);
    }

    if (_height != 0)
    {
        _ratio = (float)_width / _height;
    }
    else
    {
        _ratio = 0;
    } 
}

Texture::~Texture() {
    _SDLTexture.reset();
}

SDL_Texture* Texture::getTexture() const
{
    return _SDLTexture.get();
}

void Texture::setAlpha(Uint8 alpha) 
{
    SDL_SetTextureAlphaMod(_SDLTexture.get(), alpha);
}

int Texture::getWidth() const 
{
    return _width;
}

int Texture::getHeight() const 
{
    return _height;
}

double Texture::getRatio() const 
{
    return _ratio;
}