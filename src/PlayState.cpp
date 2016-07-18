#include "../include/PlayState.h"
#include "../include/SDLWindow.h"
#include "../include/Game.h"
#include "../include/IntroState.h"

PlayState* PlayState::_playState = NULL;

void PlayState::init(Game* game) {

    _game = game;

    _window = _game->getWindowPtr();
}

void PlayState::cleanup() {
    _window = NULL;
    _game = NULL;
}

void PlayState::handleEvents(SDL_Event& event) {

    _game->getWindowPtr()->handleEvents(event);

    if( event.type == SDL_KEYDOWN ) {

        switch( event.key.keysym.sym ) {

            case SDLK_1:
                _window->setDrawColor(0,255,0);
                break;

            case SDLK_2:
                _window->setDrawColor(0,0,255);
                break;
                
            case SDLK_3:
                _window->setDrawColor(255,0,0);
                break;

            case SDLK_BACKSPACE:
                _game->changeState(IntroState::instance());
                break;
        }
    }
}

void PlayState::update() {

}

void PlayState::draw() {

     _window->clear();


    _window->render();
}
