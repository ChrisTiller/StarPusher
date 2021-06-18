#ifndef GAMESTATEMANAGER_H
#define GAMESTATEMANAGER_H

#include <vector>
#include "SDL2/SDL.h"
#include "GameState.h"

using std::vector;

class Game;

class GameStateManager {

public:

    GameStateManager(Game*);

    void init();
    void cleanup();

    void changeState(GameState*);
    void pushState(GameState*);
    void popState();

    void handleEvents(SDL_Event& );
    void update();
    void draw();

    Game& getGame();

private:

    void RequestChangeState(GameState*, GameState*);
    void RequestPushState(GameState*, GameState*);
    void RequestPopState(GameState*);

    EventHandler<GameState*, GameState*> changeHandler;
    EventHandler<GameState*, GameState*> pushHandler;
    EventHandler<GameState*> popHandler;

    std::vector<GameState*> _states;

    Game* _game;

};

#endif
