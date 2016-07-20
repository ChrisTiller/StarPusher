#include "../include/IntroState.h"
#include "../include/SDLWindow.h"
#include "../include/Game.h"
#include "../include/PlayState.h"

IntroState* IntroState::_introState = NULL;

void IntroState::init(Game* game) {

    _game = game;

    _window = _game->getWindowPtr();

    _texture.loadTexture("star_title.png");
    _background.loadTexture("cloud_background.png");

    _texture.setAlpha(0);

    _alpha = 0;

    textRect.x = ( _window->getWidth() / 2 ) - ( _texture.getWidth() / 2 );
    textRect.y = ( _window->getHeight() / 2 ) - ( _texture.getHeight() / 2 );
    textRect.w = _texture.getWidth();
    textRect.h = _texture.getHeight();

    _window->setDrawColor(255,255,255);

}

void IntroState::cleanup() {

    _game = NULL;
    _window = NULL;

}

void IntroState::handleEvents(SDL_Event& event) {

    _game->getWindowPtr()->handleEvents(event);

    if( event.type == SDL_KEYDOWN ) {

        switch( event.key.keysym.sym ) {

           case SDLK_RETURN:
            _game->changeState(PlayState::instance());
            break;
            case SDLK_UP:
                
                break;
            case SDLK_DOWN:
            
                break;
        }
    }
}

void IntroState::update() {


    if (_alpha + 5 < 255) {

         _alpha+=5;

    } else {
        _alpha = 254;
    }

     _texture.setAlpha(_alpha);

}

void IntroState::draw() {

    _window->clear();

    _window->placeTexture(&_background, NULL, NULL);
    _window->placeTexture(&_texture, NULL, &textRect);

    _window->render();
}
