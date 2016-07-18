#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "SDL2/SDL.h"
#include "GameStateManager.h"

class GameState {
    
public:

    virtual void init(Game*) = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents( SDL_Event&) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    void changeState(GameStateManager* manager, GameState* state) {
        manager->changeState(state);
    }

protected:
    GameState() {};
};

#endif