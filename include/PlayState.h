#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "CompletedState.h"
#include "LevelEx.h"
#include "SDLWindow.h"


class PlayState : public GameState {

public:

    ~PlayState() {
    }

    void init(GameStateManager*);
    void cleanup();

    void pause();
    void resume();

    void handleEvents(SDL_Event&);
    void update();
    void draw();

    void goToNextLevel();
    void goToPreviousLevel();

    void centerCamera();

    static PlayState* instance() {
        if (!_playState) {
            _playState = new PlayState;
        }
        return _playState;
    }

protected:
    PlayState() { _manager = nullptr; }

private:
    static PlayState* _playState;

    int _levelNumber;
    LevelEx _currentLevel;

    Game* _game;
    SDLWindow* window_;

    bool _levelCompleted;

};



#endif
