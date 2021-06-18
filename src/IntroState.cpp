#include "../include/IntroState.h"
#include "../include/SDLWindow.h"
#include "../include/Game.h"
#include "../include/PlayState.h"
#include "../include/ResourceManager.h"

IntroState* IntroState::_introState = nullptr;

void IntroState::init(GameStateManager* manager) {

    _manager = manager;

    _game = &_manager->getGame();

    window_ = _manager->getGame().getWindowPtr();

    logInstance.setFileName("test");

    logInstance.log("getting star title texture");

    texture_ = ResourceManager::getInstance()->getTexture("star_title.png");

    logInstance.log("getting background texture");
    _background = ResourceManager::getInstance()->getTexture("cloud_background.png");

    texture_->setAlpha(0);

    _alpha = 0;

    textRect.x = ( window_->getWidth() / 2 ) - ( texture_->getWidth() / 2 );
    textRect.y = ( window_->getHeight() / 2 ) - ( texture_->getHeight() / 2 );
    textRect.w = texture_->getWidth();
    textRect.h = texture_->getHeight();

    _game->getCamera().setUse(false);

    window_->setDrawColor(0x1E,0x09, 255, 255);
}

void IntroState::cleanup() {

    if (_introState) {
        _manager = nullptr;
        _game = nullptr;
        window_ = nullptr;
    
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

        texture_->setAlpha(_alpha);

    } else {
        _alpha = 254;
    }


}

void IntroState::draw() {

    //window_->placeTexture(_background, NULL, NULL);
    window_->placeTexture(texture_, NULL, &textRect);
    
}