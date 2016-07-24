#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "SDL2/SDL.h"

using std::vector;

class GameState;
class Game;

class GameStateManager {

public:

    GameStateManager() {};

    void init();
    void cleanup();

    void changeState(GameState*);
    void pushState(GameState*);
    void popState();

    void handleEvents(SDL_Event& );
    void update();
    void draw();

    void setGame(Game*);
private:

    vector<GameState*> _states;

    Game* _game;

};

#endif
