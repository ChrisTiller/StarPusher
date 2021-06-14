#ifndef COMPlETEDSTATE_H
#define COMPlETEDSTATE_H

#include "GameState.h"
#include "Texture.h"

class CompletedState : public GameState {

public:

    ~CompletedState() {
    }

    void init(GameStateManager*);
    void cleanup();

    void pause();
    void resume();

    void handleEvents(SDL_Event&);
    void update();
    void draw();

    static CompletedState* instance() {
        if (!_completedState) {
            _completedState = new CompletedState;
        }
        return _completedState;
    }

protected:

    CompletedState() {}

private:

    static CompletedState* _completedState;

    Game* _game;

    Texture _background;
    Texture _picture;

    bool _levelCompleted;
};

#endif
