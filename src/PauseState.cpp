#include "../include/PauseState.h"
#include "../include/GameStateManager.h"
#include "../include/Game.h"

PauseState* PauseState::instance_ = NULL;

PauseState::PauseState() {
    _game = nullptr; 
    window_ = nullptr;

    //_menuRect.backgroundColor()->setAlpha(190);
    _menuRect.background_color_.a = 190;
    //_menuRect.backgroundColor3().setAlpha(190);
    _menuRect.setLocation(100, 0);
}

PauseState::~PauseState() {
    _game = nullptr; 
     window_ = nullptr;
}

PauseState* PauseState::instance()  {
        if (!instance_) {
            instance_ = new PauseState;
        }
        return instance_;
    }

void PauseState::init(GameStateManager* manager) {
    _manager = manager;

    _game = &_manager->getGame();

    window_ = _game->getWindowPtr();
}

void PauseState::cleanup() {

    if (instance_) {
        delete instance_;
        instance_ = nullptr;
    }

}

void PauseState::pause() {

}

void PauseState::resume() {

}

void PauseState::handleEvents(SDL_Event& event) {

    if( event.type == SDL_KEYDOWN ) {

        switch( event.key.keysym.sym ) {

            case SDLK_ESCAPE:
                RequestPopState((GameState*)this);
                break;
        }
    }

}

void PauseState::update() {

}

void PauseState::draw() {

    _menuRect.setSize(300, window_->getHeight());

    _menuRect.draw(window_->getRenderer());

}