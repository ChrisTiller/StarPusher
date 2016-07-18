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

bool Texture::loadTexture(string fileName, SDL_Renderer* renderer) {
    
    _texture = SDL_CreateTextureFromSurface(renderer, IMG_Load(fileName.c_str()));

    if (!_texture) {
        return false;
    }

    return true;
}