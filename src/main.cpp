#include "SDL2/SDL.h"
#include "../include/Game.h"

int main(int, char**) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }

    Game starPusher("Star Pusher", 1280, 768);

    starPusher.run();

    return 0;

}
