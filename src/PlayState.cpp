#include "../include/PlayState.h"
#include "../include/SDLWindow.h"
#include "../include/Game.h"
#include "../include/IntroState.h"

#include <iostream>

PlayState* PlayState::_playState = NULL;

void PlayState::init(Game* game) {

    _game = game;

    _window = _game->getWindowPtr();

    _game->getLevel().gotoNextLevel();

    _game->getCamera().setUse(true);

    //_window->setDrawColor(0x1E,0x09,255);
    //_window->setDrawColor(0,0,0);
    //_window->setDrawColor(0xD9, 0xE9, 0xF);
    //_window->setDrawColor(176, 209, 255);
    _window->setDrawColor(135,206,250);

    _levelCompleted = false;
}

void PlayState::cleanup() {

    _window = NULL;
    _game = NULL;
}

void PlayState::handleEvents(SDL_Event& event) {

    _game->getWindowPtr()->handleEvents(event);

    if( event.type == SDL_KEYDOWN ) {

        switch( event.key.keysym.sym ) {

            case SDLK_UP:
                _game->getLevel().movePlayer(UP);
                break;

            case SDLK_DOWN:
                _game->getLevel().movePlayer(DOWN);
                break;

            case SDLK_LEFT:
                _game->getLevel().movePlayer(LEFT);
                break;

            case SDLK_RIGHT:
                _game->getLevel().movePlayer(RIGHT);
                break;

            case SDLK_BACKSPACE:
                _game->getGameStateManager().pushState(IntroState::instance());
                break;

            case SDLK_c:
                _game->getCamera().setXYPos(0,0);
                break;

            case SDLK_n:
                _game->getLevel().gotoPrevLevel();
                _game->getCamera().setXYPos(0,0);
                break;

            case SDLK_m:
                _game->getLevel().gotoNextLevel();
                _game->getCamera().setXYPos(0,0);
                break;

            case SDLK_r:
                _game->getLevel().resetLevel();
                _game->getCamera().setXYPos(0,0);
                break;

        }
    }
}

void PlayState::update() {

    if  (_levelCompleted) {
        _game->getGameStateManager().changeState(CompletedState::instance());
    }

}

void PlayState::draw() {

    _window->clear();

    //_window->placeTexture(&_texture, NULL, NULL);

    _game->getLevel().renderLevel();

    if (_game->getLevel().levelCompleted()) {
        _levelCompleted = true;
    }

    //_window->placeTexture(&_player, NULL, &textRect);

    _window->render();
}
