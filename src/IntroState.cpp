#include "../include/IntroState.h"
#include "../include/SDLWindow.h"
#include "../include/Game.h"
#include "../include/PlayState.h"

IntroState* IntroState::_introState = NULL;

void IntroState::init(Game* game) {

    _game = game;

    _window = _game->getWindowPtr();

    _texture.loadTexture("../resources/images/star_title.png", _window->getRenderer());

    SDL_SetTextureAlphaMod(_texture.getTexture(), 0);

    _alpha = 0;

    int w,h;

    SDL_QueryTexture(_texture.getTexture(), NULL, NULL, &w, &h);

    textRect.x = ( _window->getWidth() / 2 ) - ( w / 2 );
    textRect.y = ( _window->getHeight() / 2 ) - ( h / 2 );
    textRect.w = w;
    textRect.h = h;

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

        }
    }
}

void IntroState::update() {


    if (_alpha + 5 < 255) {

         _alpha+=5;

    } else {
        _alpha = 254;
    }

     SDL_SetTextureAlphaMod(_texture.getTexture(), _alpha);

}

void IntroState::draw() {

    _window->clear();

    _window->placeTexture(&_texture, NULL, &textRect);

    _window->render();
}
