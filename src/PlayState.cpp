#include "../include/PlayState.h"
#include "../include/SDLWindow.h"
#include "../include/Game.h"
#include "../include/IntroState.h"

#include <iostream>

PlayState* PlayState::_playState = NULL;

void PlayState::init(Game* game) {

    _game = game;

    _window = _game->getWindowPtr();

    _levelNumber = 1;
    _currentLevel = _game->getResourceManager()->getInstance()->getLevel(1);

    _game->getCamera().setUse(true);

    _window->setDrawColor(135,206,250);

    _levelCompleted = false;

    centerCamera();
}

void PlayState::cleanup() {

    _window = nullptr;
    _game = nullptr;

    delete _playState;
    _playState = nullptr;
}

void PlayState::handleEvents(SDL_Event& event) {

    _game->getWindowPtr()->handleEvents(event);

    if( event.type == SDL_KEYDOWN ) {

        switch( event.key.keysym.sym ) {

            case SDLK_UP:
                _currentLevel.movePlayerUp();
                break;

            case SDLK_DOWN:
                _currentLevel.movePlayerDown();
                break;

            case SDLK_LEFT:
                _currentLevel.movePlayerLeft();
                break;

            case SDLK_RIGHT:
                _currentLevel.movePlayerRight();
                break;

            case SDLK_BACKSPACE:
                _game->getGameStateManager().pushState(IntroState::instance());
                break;

            case SDLK_c:
                centerCamera();
                break;

            case SDLK_n:
                goToPreviousLevel();
                centerCamera();                
                break;

            case SDLK_m:
                goToNextLevel();
                centerCamera();                
                break;

            case SDLK_r:
                _currentLevel = _game->getResourceManager()->getInstance()->getLevel(_levelNumber);
                centerCamera();
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

    SDL_Rect rct = _game->getCamera().getRect();

    for (auto blockToRender : _currentLevel.getVisibleBlocks(rct)) {

        _window->placeTexture(blockToRender->getTexture(), \
                              blockToRender->getLocation().getX() - _game->getCamera().getXPos(), \
                              blockToRender->getLocation().getY() - _game->getCamera().getYPos());

        blockToRender = nullptr;
    }

    _window->render();

    if (_currentLevel.isCompleted()) {
        goToNextLevel();
        centerCamera();
    }
}

void PlayState::goToPreviousLevel() {
    if (--_levelNumber < 1) {
        _levelNumber = 1;
    }
    _currentLevel = _game->getResourceManager()->getInstance()->getLevel(_levelNumber);
}

void PlayState::goToNextLevel() {
    if (++_levelNumber > 50) {
        _levelNumber = 50;
    }
    _currentLevel = _game->getResourceManager()->getInstance()->getLevel(_levelNumber);
}

void PlayState::centerCamera() {
    _game->getCamera().setXYPos(-(( _window->getWidth() / 2 ) - ( _currentLevel.getWidth() / 2 )), \
                                -(( _window->getHeight() / 2 ) - ( _currentLevel.getHeight() / 2 )));
}

