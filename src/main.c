#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>

#include "../include/button.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;

Button btn;

int running = 1;

int renderWindow() {
    window = SDL_CreateWindow("Hello, World!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 700, 500, SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        printf("Error: SDL_CreateWindow failure: %s\n", SDL_GetError());
        return 1;
    } else {
        printf("SDL_CreateWindow success\n");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Error: SDL_CreateRenderer failure: %s\n", SDL_GetError());
        return 1;
    } else {
        printf("SDL_CreateRenderer success\n");
    }

    btn = createButton(10, 10, 10, 10, (SDL_Color){0, 255, 255}, (SDL_Color){0, 255, 0}, (SDL_Color){255, 255, 255}, 0);
}

int main(int argc, char **argv) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Error: SDL_Init failure: %s\n", SDL_GetError());
        return 1;
    } else {
        printf("SDL_Init success\n");
    }

    renderWindow();

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderButton(&btn, renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}