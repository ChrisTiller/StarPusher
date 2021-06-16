#include "../include/SDLWindow.h"
#include "../include/Texture.h"

#include <iostream>

SDLWindow::SDLWindow(string name, int width, int height)
    : _r(255), _g(255), _b(255) {

    _windowName = name;
    _width = width;
    _height = height;

    _window = SDL_CreateWindow(_windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!_window) {
        printf("Window Creation Failed! SDL Error: %s\n", SDL_GetError());

        return;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!_renderer) {
        printf("Renderer Creation Failed! SDL Error %s\n", SDL_GetError());
        SDL_DestroyWindow(_window);
        _window = NULL;

        return;
    }

    _shown = true;
    _minimized = false;

    _a = 255;

}

SDLWindow::~SDLWindow() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    _renderer = NULL;
    _window = NULL;
}

int SDLWindow::getWidth() const {
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(_window , &w, &h);
    return w;
}

int SDLWindow::getHeight() const {
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(_window , &w, &h);
    return h;
}

void SDLWindow::focus() {

    if (!_shown) {
        SDL_ShowWindow(_window);
        _shown = true;
    }

    SDL_RaiseWindow(_window);

}

void SDLWindow::handleEvents(SDL_Event& event) {

    switch (event.window.event) {

        case SDL_WINDOWEVENT_SHOWN:
            _minimized = false;
            _shown = true;
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            _shown = false;
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_RenderPresent(_renderer);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            _minimized = true;
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            _minimized = false;
            break;
        case SDL_WINDOWEVENT_RESTORED:
            _minimized = false;
            break;

    }

}

void SDLWindow::clear() {

     if (!_minimized) {
        SDL_SetRenderDrawColor(_renderer, _r, _g, _b, _a);
        SDL_RenderClear(_renderer);
        SDL_RenderFillRect(_renderer, NULL);
    }
}

void SDLWindow::placeTexture(Texture* texture, SDL_Rect* src, SDL_Rect* dst) {

    if (!_minimized) {
        SDL_RenderCopy(_renderer, texture->getTexture(), src, dst);
    }

}

void SDLWindow::placeTexture(Texture* texture, int x, int y, SDL_Rect* clip) {

    SDL_Rect dst;

    dst.x = x;
    dst.y = y;
    dst.w = texture->getWidth();
    dst.h = texture->getHeight();

    placeTexture(texture, clip, &dst);

}

void SDLWindow::render() {

    if (!_minimized) {
        SDL_RenderPresent(_renderer);
    }
}

void SDLWindow::setDrawColor(int r, int g, int b) {
    _r = r;
    _g = g;
    _b = b;
}

void SDLWindow::setDrawColor(int r, int g, int b, int a) {
    _r = r;
    _g = g;
    _b = b;
    _a = a;
}

SDL_Renderer* SDLWindow::getRenderer() const {
    return _renderer;
}

// void SDLWindow::setTarget(Texture& target) {


//      target.setTexture(SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _width, _height));

//      if (target.getTexture() == NULL) {
//         std::cout << "Unable to create blank texture. SDL_Error: " << SDL_GetError() << std::endl;
//     }

//     SDL_SetRenderTarget(_renderer, target.getTexture());
// }

void SDLWindow::setDefaultTarget() {
    SDL_SetRenderTarget(_renderer, NULL);
}
