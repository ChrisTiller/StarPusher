#include "../include/PlayState.h"
#include "../include/SDLWindow.h"
#include "../include/Game.h"
#include "../include/IntroState.h"

PlayState* PlayState::_playState = NULL;

void PlayState::init(Game* game) {

    _game = game;

    _window = _game->getWindowPtr();

    _texture.loadTexture("cloud_background.png");
    _player.loadTexture("boy.png");

    textRect.x = ( _window->getWidth() / 2 ) - ( _player.getWidth() / 2 );
    textRect.y = ( _window->getHeight() / 2 ) - ( _player.getHeight() / 2 );
    textRect.w = _player.getWidth();
    textRect.h = _player.getHeight();

    _window->setDrawColor(0x1E,0x09,255);
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
                textRect.y-=_player.getHeight();
                break;

            case SDLK_DOWN:
                textRect.y+=_player.getHeight();
                break;
                
            case SDLK_LEFT:
                textRect.x-=_player.getWidth();
                break;
            
            case SDLK_RIGHT:
                textRect.x+=_player.getWidth();
                break;

            case SDLK_BACKSPACE:
                _game->getGameStateManager().changeState(IntroState::instance());
                break;
    
        }
    }
}

void PlayState::update() {

    if (textRect.x + textRect.w > _window->getWidth()) {
        textRect.x = _window->getWidth() - textRect.w;
    }
    if (textRect.y + textRect.h > _window->getHeight()) {
        textRect.y = _window->getHeight() - textRect.h;
    }
    if (textRect.x < 0) {
        textRect.x = 0;
    }
    if (textRect.y < 0) {
        textRect.y = 0;
    }
}

void PlayState::draw() {

    _window->clear();

    //_window->placeTexture(&_texture, NULL, NULL);

    _window->placeTexture(&_player, NULL, &textRect);

    _window->render();
}
