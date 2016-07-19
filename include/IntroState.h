#ifndef INTROSTATE_H
#define INTROSTATE_H

#include "SDL2/SDL.h"
#include "GameState.h"
#include "Texture.h"


class SDLWindow;

class IntroState : public GameState {

public:

    ~IntroState() {
        cleanup();
    }

    void init(Game*);
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
    IntroState() {}

private:
    static IntroState* _introState;

    Game* _game;
    SDLWindow* _window;
    Texture _texture;
    Texture _background;

    Uint8 _alpha;

    SDL_Rect textRect;

};



#endif
