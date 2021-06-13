#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"
#include "CompletedState.h"
#include "LevelEx.h"

class SDLWindow;

class PlayState : public GameState {

public:

    ~PlayState() {
        cleanup();
    }

    void init(Game*);
    void cleanup();

    void pause() {}
    void resume() {}

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
    PlayState() {}

private:
    static PlayState* _playState;

    int _levelNumber;
    LevelEx _currentLevel;

    Game* _game;
    SDLWindow* _window;

    bool _levelCompleted;

};



#endif
