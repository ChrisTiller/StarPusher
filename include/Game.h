#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "stdio.h"
#include "SDLWindow.h"
#include "GameStateManager.h"
#include "ResourceManager.h"
#include "Level.h"
#include <vector>

using std::vector;

class Game {

public:
    Game(string, int, int);
    ~Game();

    void run();

    bool isRunning();
    void quit();

    GameStateManager& getGameStateManager();

    SDLWindow* getWindowPtr();

    ResourceManager* getResourceManager();

    Level& getLevel();

private:

    SDLWindow  _window;

    GameStateManager _manager;
    ResourceManager* _resourceManager;
    Level _level;

    bool _running;

};

#endif