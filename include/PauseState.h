#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include "SDLWindow.h"


class PauseState : public GameState {

public:

    ~PauseState();

    void init(GameStateManager*);
    void cleanup();

    void pause();
    void resume();

    void handleEvents(SDL_Event&);
    void update();
    void draw();

    static PauseState* instance();

protected:
    PauseState();

private:
    static PauseState* _instance;

    Game* _game;
    SDLWindow* _window;

};



#endif
