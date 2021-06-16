#include "../include/PauseState.h"

PauseState* PauseState::_instance = NULL;

PauseState::PauseState() {
     _game = nullptr; 
     _window = nullptr;
}

PauseState::~PauseState() {
    _game = nullptr; 
     _window = nullptr;
}

PauseState* PauseState::instance()  {
        if (!_instance) {
            _instance = new PauseState;
        }
        return _instance;
    }

void PauseState::init(GameStateManager*) {

}

void PauseState::cleanup() {

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

}