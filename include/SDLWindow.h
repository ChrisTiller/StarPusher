#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <string>
#include "SDL2/SDL.h"

#include "Event.h"
#include "Color.h"

class Texture;

class SDLWindow {

public:
    SDLWindow(std::string, int, int);
    ~SDLWindow();

    int getWidth() const;
    int getHeight() const;

    void focus();
    void handleEvents(SDL_Event&);

    void clear();
    void placeTexture(Texture*, SDL_Rect*, SDL_Rect*);
    void placeTexture(Texture*, int, int, SDL_Rect* = NULL);
    void render();

    void setClearColor(const Color&);
    void setClearColor(int, int, int, int = 255);

    void setDrawColor(const Color&);
    void setDrawColor(int, int, int, int = 255);

    SDL_Renderer* getRenderer() const;

    void setDefaultTarget();

    Event<int, int> WindowSizeChanged;

private:

    SDL_Window* window_;
    SDL_Renderer* renderer_;

    int _width;
    int _height;

    Color clear_color_;
    Color draw_color_;

    std::string _windowName;

    bool _shown;
    bool _minimized;

};

#endif
