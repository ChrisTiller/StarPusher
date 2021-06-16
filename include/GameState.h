#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "SDL2/SDL.h"
#include "Event.h"

class GameStateManager;
class Game;

class GameState {
    
public:

    virtual void init(GameStateManager*) = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents( SDL_Event&) = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    
    Event<GameState*, GameState*> RequestChangeState;
    Event<GameState*> RequestPopState;
    

protected:
    
    GameState() {};

    GameStateManager* _manager;

private:   

};

#endif