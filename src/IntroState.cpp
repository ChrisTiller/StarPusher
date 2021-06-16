#include "../include/IntroState.h"
#include "../include/SDLWindow.h"
#include "../include/Game.h"
#include "../include/PlayState.h"
#include "../include/ResourceManager.h"

IntroState* IntroState::_introState = nullptr;

void IntroState::init(GameStateManager* manager) {

    _manager = manager;

    _game = &_manager->getGame();

    _window = _manager->getGame().getWindowPtr();

    logInstance.setFileName("test");

    logInstance.log("getting star title texture");

    _texture = ResourceManager::getInstance()->getTexture("star_title.png");

    logInstance.log("getting background texture");
    _background = ResourceManager::getInstance()->getTexture("cloud_background.png");

    _texture->setAlpha(0);

    _alpha = 0;

    textRect.x = ( _window->getWidth() / 2 ) - ( _texture->getWidth() / 2 );
    textRect.y = ( _window->getHeight() / 2 ) - ( _texture->getHeight() / 2 );
    textRect.w = _texture->getWidth();
    textRect.h = _texture->getHeight();

    _game->getCamera().setUse(false);

    _window->setDrawColor(0x1E,0x09,255);
}

void IntroState::cleanup() {

    if (_introState) {
        _manager = nullptr;
        _game = nullptr;
        _window = nullptr;
    
        delete _introState;
        _introState = nullptr;
    }    
}

void IntroState::handleEvents(SDL_Event& event) {

    if( event.type == SDL_KEYDOWN ) {

        switch( event.key.keysym.sym ) {

           case SDLK_RETURN:
            RequestChangeState((GameState*)this, (GameState*)PlayState::instance());
            break;
            case SDLK_UP:

                break;
            case SDLK_DOWN:

                break;
        }
    }
}

void IntroState::update() {


    if (_alpha + 2 < 255) {

         _alpha+=2;

        _texture->setAlpha(_alpha);

    } else {
        _alpha = 254;
    }


}

void IntroState::draw() {

    //_window->placeTexture(_background, NULL, NULL);
    _window->placeTexture(_texture, NULL, &textRect);
    
}