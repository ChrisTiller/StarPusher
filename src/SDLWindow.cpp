#include "../include/SDLWindow.h"
#include "../include/Texture.h"

#include <iostream>

SDLWindow::SDLWindow(string name, int width, int height)
    : clear_color_(135,206,250), draw_color_(known_colors::kBlack) {

    _windowName = name;
    _width = width;
    _height = height;

    window_ = SDL_CreateWindow(_windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window_) {
        printf("Window Creation Failed! SDL Error: %s\n", SDL_GetError());

        return;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer_) {
        printf("Renderer Creation Failed! SDL Error %s\n", SDL_GetError());
        SDL_DestroyWindow(window_);
        window_ = NULL;

        return;
    }

    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);

    _shown = true;
    _minimized = false;
}

SDLWindow::~SDLWindow() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);

    renderer_ = NULL;
    window_ = NULL;
}

int SDLWindow::getWidth() const {
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(window_ , &w, &h);
    return w;
}

int SDLWindow::getHeight() const {
    int w = 0;
    int h = 0;
    SDL_GetWindowSize(window_ , &w, &h);
    return h;
}

void SDLWindow::focus() {

    if (!_shown) {
        SDL_ShowWindow(window_);
        _shown = true;
    }

    SDL_RaiseWindow(window_);

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
            SDL_RenderPresent(renderer_);
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
        case SDL_WINDOWEVENT_RESIZED:
            int w;
            int h;

            SDL_GetWindowSize(window_, &w, &h);

            WindowSizeChanged(w, h);
            break;
    }

}

void SDLWindow::clear() {

     if (!_minimized) {
        SDL_SetRenderDrawColor(renderer_, clear_color_.r, clear_color_.g, clear_color_.b, clear_color_.a);
        SDL_RenderClear(renderer_);
        SDL_RenderFillRect(renderer_, NULL);
        SDL_SetRenderDrawColor(renderer_, draw_color_.r, draw_color_.g, draw_color_.b, draw_color_.a);
    }
}

void SDLWindow::placeTexture(Texture* texture, SDL_Rect* src, SDL_Rect* dst) {

    if (!_minimized) {
        SDL_RenderCopy(renderer_, texture->getTexture(), src, dst);
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
        SDL_RenderPresent(renderer_);
    }
}

void SDLWindow::setClearColor(const Color& new_color) {
    clear_color_.r = new_color.r;
    clear_color_.g = new_color.g;
    clear_color_.b = new_color.b;
    clear_color_.a = new_color.a;
}

void SDLWindow::setClearColor(int r, int g, int b, int a) {
    clear_color_.r = r;
    clear_color_.g = g;
    clear_color_.b = b;
    clear_color_.a = a;
}

void SDLWindow::setDrawColor(const Color& new_color) {
    draw_color_.r = new_color.r;
    draw_color_.g = new_color.g;
    draw_color_.b = new_color.b;
    draw_color_.a = new_color.a;

    SDL_SetRenderDrawColor(renderer_, draw_color_.r, draw_color_.g, draw_color_.b, draw_color_.a);
}

void SDLWindow::setDrawColor(int r, int g, int b, int a) {
    draw_color_.r = r;
    draw_color_.g = g;
    draw_color_.b = b;
    draw_color_.a = a;

    SDL_SetRenderDrawColor(renderer_, draw_color_.r, draw_color_.g, draw_color_.b, draw_color_.a);
}

SDL_Renderer* SDLWindow::getRenderer() const {
    return renderer_;
}

void SDLWindow::setDefaultTarget() {
    SDL_SetRenderTarget(renderer_, NULL);
}
