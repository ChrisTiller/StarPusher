#include "../include/Game.h"
#include "../include/IntroState.h"

Game::Game(string name, int width, int height) 
    : _window(name, width, height), _running(true) {    

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return;
    }

    _manager.setGame(this);

    _manager.changeState(IntroState::instance());

}

Game::~Game() {
   SDL_Quit();
}

void Game::run() {

    SDL_Event event;

    while (isRunning()) {

        while (SDL_PollEvent(&event) != 0) {

            if (event.type == SDL_QUIT) {
                quit();
            }

            switch (event.window.event) {

                case SDL_WINDOWEVENT_CLOSE:
                    quit();
                    break;

            }

            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit();
                    break;
            }

            _manager.handleEvents(event);

        }

        _manager.update();
        _manager.draw();
    }

}

bool Game::isRunning() {
    return _running;
}

void Game::quit() {
    _running = false;
}

SDLWindow* Game::getWindowPtr() {
    return &_window;
}

void Game::changeState(GameState* newState) {
    _manager.changeState(newState);
}