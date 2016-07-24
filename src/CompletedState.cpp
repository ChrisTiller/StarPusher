#include "../include/CompletedState.h"
#include "../include/SDLWindow.h"
#include "../include/Game.h"
#include "../include/IntroState.h"
#include "../include/PlayState.h"

CompletedState* CompletedState::_completedState = NULL;

void CompletedState::init(Game* game) {


    _game = game;

    _window = _game->getWindowPtr();

    //_game->getWindowPtr()->setTarget(_background);

    _game->getWindowPtr()->setDrawColor(0, 0, 0, 255);

    _game->getWindowPtr()->clear();

    //_game->getLevel().renderLevel();

    //_game->getWindowPtr()->setDefaultTarget();

    //_window->setDrawColor(0x1E,0x09,255, 0);

    //_window->clear();

    //_game->getWindowPtr()->placeTexture(&_background, 0, 0);

    _game->getWindowPtr()->render();

    //_window->setDrawColor(0x1E,0x09,255, 10);

}

void CompletedState::cleanup() {

}

void CompletedState::pause() {

}

void CompletedState::resume() {

}

void CompletedState::handleEvents(SDL_Event& event) {

    _game->getWindowPtr()->handleEvents(event);

    if( event.type == SDL_KEYDOWN ) {

        switch( event.key.keysym.sym ) {

            case SDLK_UP:
                break;

            case SDLK_DOWN:
                break;

            case SDLK_LEFT:
                break;

            case SDLK_RIGHT:
                break;

            case SDLK_BACKSPACE:
                _game->getGameStateManager().changeState(PlayState::instance());
                break;

            case SDLK_c:
                break;

            case SDLK_n:
                break;

            case SDLK_m:
                break;

            case SDLK_r:
                break;

        }
    }
}

void CompletedState::update() {

}

void CompletedState::draw() {

    //_window->clear();

    //_window->placeTexture(&_background, 0, 0);

    //_window->render();

}
