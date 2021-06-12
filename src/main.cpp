#include "SDL2/SDL.h"
#include "../include/Game.h"

int main(int, char**) {

    logInstance.setFileName("test");

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    logInstance.log("initialize game object");

    Game starPusher("Star Pusher", 1280, 768);

    logInstance.log("run call");

    starPusher.run();

    return 0;

}
