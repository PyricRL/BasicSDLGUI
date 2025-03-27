#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "SDL_ttf.h"

#include "../include/button.h"
#include "../include/text.h"

//gcc src/main.c src/button.c src/text.c -IC:/msys64/mingw64/include/SDL2 -LC:/msys64/mingw64/lib -lSDL2 -lSDL2main -lSDL2_ttf -o main

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Event event;

Button btn;
TextBox text;

int running = 1;

int renderWindow() {
    if (TTF_Init() == -1) {
        printf("Error: TTF_Init failure: %s\n", TTF_GetError());
        return 1;
    }

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

    btn = createButton((700 - 200) / 2, 400, 200, 50, 0, (SDL_Color){0, 255, 255}, (SDL_Color){0, 255, 0}, (SDL_Color){255, 255, 255}, (SDL_Color){0, 0, 0}, 100, "Click to start auto clicker!");
    //text = createTextBox(30, 30, 50, 50, (SDL_Color){255, 255, 255}, "Hi");
    
    return 0;
}

int main(int argc, char **argv) {
    printf("Initializing SDL...\n");
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("Error: SDL_Init failure: %s\n", SDL_GetError());
        return 1;
    } else {
        printf("SDL_Init success\n");
    }

    if (renderWindow() != 0) {
        printf("Error: Render window failure");
        return 1;
    }

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        renderButton(&btn, renderer);
        handleButtonEvent(&btn, event);
        //renderTextBox(&text, renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    free(text.text);
    TTF_Quit();
    SDL_Quit();
    return 0;
}