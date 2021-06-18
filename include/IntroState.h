#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "SDL2/SDL.h"
#include "GameState.h"
#include "Texture.h"
#include "SDLWindow.h"

class IntroState : public GameState {

public:

    ~IntroState() {
    }

    void init(GameStateManager*);
    void cleanup();

    void pause() {}
    void resume() {}

    void handleEvents(SDL_Event&);
    void update();
    void draw();

    static IntroState* instance() {
        if (!_introState) {
            _introState = new IntroState;
        }
        return _introState;
    }

protected:
    IntroState() { _manager = nullptr; }

private:

    static IntroState* _introState;

    Game* _game;
    SDLWindow* window_;
    Texture* texture_;
    Texture* _background;

    Uint8 _alpha;

    SDL_Rect textRect;

};



#endif
