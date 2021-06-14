#include "../include/CompletedState.h"
#include "../include/SDLWindow.h"
#include "../include/Game.h"
#include "../include/IntroState.h"
#include "../include/PlayState.h"

CompletedState* CompletedState::_completedState = NULL;

void CompletedState::init(GameStateManager* manager) {


    _manager = manager;

    _game = &_manager->getGame();

    SDLWindow* _window = _game->getWindowPtr();

    _window->setDrawColor(0, 0, 0, 255);

    _window->clear();

    _window->render();

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
                _manager->changeState(PlayState::instance());
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
