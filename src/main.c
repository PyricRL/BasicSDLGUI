#include <SDL2/SDL.h>
#include "SDL_ttf.h"
#include <stdio.h>
#include "../include/main.h"

EXPORT void initializeSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }
    if (TTF_Init() == -1) {
        printf("TTF_Init failed: %s\n", TTF_GetError());
    }
}