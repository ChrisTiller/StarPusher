#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "stdio.h"
#include "SDLWindow.h"
#include "GameStateManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Log.h"

class Game {

public:
    Game(string, int, int);
    ~Game();

    void run();

    bool isRunning();
    void quit();

    GameStateManager& getGameStateManager();

    SDLWindow* getWindowPtr();

    Camera& getCamera();

private:

    SDLWindow  window_;

    GameStateManager _manager;
    Camera _camera;

    bool _running;

};

#endif
