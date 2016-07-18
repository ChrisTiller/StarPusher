#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include "SDL2/SDL.h"
#include <string>

using std::string;

class SDLWindow {

public:
    SDLWindow(string, int, int);
    ~SDLWindow();

    int getWidth() const;
    int getHeight() const;

    void focus();
    void handleEvents(SDL_Event&);
    
    void clear();
    void placeTexture(SDL_Texture*, SDL_Rect*, SDL_Rect*);
    void render();

    void setDrawColor(int , int , int );    

    SDL_Renderer* getRenderer() const;

private:

    SDL_Window* _window;
    SDL_Renderer* _renderer;

    int _width;
    int _height;

    int _r;
    int _g;
    int _b;

    string _windowName;    

    bool _shown;
    bool _minimized;

};

#endif