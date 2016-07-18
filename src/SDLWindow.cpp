#include "../include/SDLWindow.h"
#include "../include/Texture.h"

SDLWindow::SDLWindow(string name, int width, int height) 
    : _r(255), _g(255), _b(255) {

    _windowName = name;
    _width = width;
    _height = height;

    _window = SDL_CreateWindow(_windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN);

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

}

SDLWindow::~SDLWindow() {
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);

    _renderer = NULL;
    _window = NULL;
}

int SDLWindow::getWidth() const {
    return _width;
}

int SDLWindow::getHeight() const {
    return _height;
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
        SDL_SetRenderDrawColor(_renderer, _r, _g, _b, 255);
        SDL_RenderFillRect(_renderer, NULL);
        SDL_RenderClear(_renderer);

    }

}

void SDLWindow::placeTexture(Texture* texture, SDL_Rect* src, SDL_Rect* dst) {

    if (!_minimized) {
        SDL_RenderCopy(_renderer, texture->getTexture(), src, dst);
    }

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

SDL_Renderer* SDLWindow::getRenderer() const {
    return _renderer;
}