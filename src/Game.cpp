#include "../include/Game.h"
#include "../include/IntroState.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_SECOND = 1000 / SCREEN_FPS;


Game::Game(string name, int width, int height)
    : window_(name, width, height), _running(true), _manager(this), _camera(&window_) {


    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return;
    }

    ResourceManager::getInstance()->setRenderer(getWindowPtr()->getRenderer());
    ResourceManager::getInstance()->setResourcePath("../resources");
    ResourceManager::getInstance()->readAllLevels("../resources/levels/levels.txt");

    logInstance.log("Change State");
    _manager.changeState(IntroState::instance());

}

Game::~Game() {
    ResourceManager::getInstance()->cleanUp();
    getGameStateManager().cleanup();
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
                    //quit();
                    break;
            }

            _camera.handleEvents(event);
            window_.handleEvents(event);
            _manager.handleEvents(event);

        }

        _manager.update();
        _camera.update();

        window_.clear();

        _manager.draw();

        window_.render();

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
    return &window_;
}

GameStateManager& Game::getGameStateManager() {
    return _manager;
}

Camera& Game::getCamera() {
    return _camera;
}
