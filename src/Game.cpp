#include "../include/Game.h"
#include "../include/IntroState.h"


const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_SECOND = 1000 / SCREEN_FPS;


Game::Game(string name, int width, int height)
    : _window(name, width, height), _running(true), _level("../resources/levels/levels.txt") {

    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return;
    }

    _manager.setGame(this);

    _resourceManager->getInstance()->setGame(this);
    _resourceManager->getInstance()->setResourcePath("../resources");


    _manager.changeState(IntroState::instance());

    _level.setGame(this);

}

Game::~Game() {
    IMG_Quit();
    SDL_Quit();
}

void Game::run() {

    SDL_Event event;

    Uint32 startingTicks;

    while (isRunning()) {

        startingTicks = SDL_GetTicks();

        while (SDL_PollEvent(&event) != 0) {

            if (event.type == SDL_QUIT) {
               quit();
            }

            switch (event.window.event) {

                case SDL_WINDOWEVENT_CLOSE:
                    quit();
                    break;

            }

            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit();
                    break;
            }


            _camera.handleEvents(event);
            _manager.handleEvents(event);

        }

        _manager.update();
        _camera.update();
        _manager.draw();

        Uint32 endingTicks = SDL_GetTicks() - startingTicks;
        if ( endingTicks < SCREEN_TICKS_PER_SECOND ){
            SDL_Delay( SCREEN_TICKS_PER_SECOND - endingTicks);
        }
    }

}

bool Game::isRunning() {
    return _running;
}

void Game::quit() {
    _running = false;
}

SDLWindow* Game::getWindowPtr() {
    return &_window;
}

GameStateManager& Game::getGameStateManager() {
    return _manager;
}

ResourceManager* Game::getResourceManager() {
    return _resourceManager;
}

Level& Game::getLevel() {
    return _level;
}

Camera& Game::getCamera() {
    return _camera;
}
