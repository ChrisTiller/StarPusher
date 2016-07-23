#include "../include/Texture.h"
#include "../include/ResourceManager.h"
#include "SDL2/SDL_image.h"
#include <iostream>



Texture::Texture() {

}

Texture::Texture(string name) {
    if (!loadTexture(name)) {
        return;
    }
}


SDL_Texture* Texture::getTexture() const {
    return _texture;
}


void Texture::setAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(_texture, alpha);
}

bool Texture::loadTexture(string name) {

    if (name == "") {
        _texture = NULL;
        return true;
    }

    _texture = _resourceManager->getInstance()->getTexture(name);

    if (!_texture) {
        printf("false");
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
