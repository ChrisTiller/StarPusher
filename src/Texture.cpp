#include "../include/Texture.h"
#include "SDL2/SDL_image.h"

Texture::Texture() {
    _texture = NULL;
}

Texture::Texture(string fileName, SDL_Renderer* renderer) {
    if (!loadTexture(fileName, renderer)) {
        return;
    }
}

Texture::~Texture() {
    SDL_DestroyTexture(_texture);
    _texture = NULL;
}

SDL_Texture* Texture::getTexture() const {
    return _texture;
}

void Texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(_texture, alpha);
}

bool Texture::loadTexture(string fileName, SDL_Renderer* renderer) {
    
    _texture = SDL_CreateTextureFromSurface(renderer, IMG_Load(fileName.c_str()));

    if (!_texture) {
        return false;
    }

    SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);

    _ratio = (float)_width / _height;

    return true;
}

int Texture::getWidth() const {
    return _width;
}

int Texture::getHeight() const {
    return _height;
}

double Texture::getRatio() const {
    return _ratio;
}

void Texture::deleteTexture() {
    if (_texture) {
        SDL_DestroyTexture(_texture);
        _texture = NULL;
    }
}