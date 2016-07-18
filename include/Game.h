#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "stdio.h"
#include "SDLWindow.h"
#include "GameStateManager.h"
#include <vector>

using std::vector;

class Game {

public:
    Game(string, int, int);
    ~Game();

    void run();

    bool isRunning();
    void quit();

    void changeState(GameState* newState);

    SDLWindow* getWindowPtr();

private:

    SDLWindow  _window;

    GameStateManager _manager;

    bool _running;

};

#endif