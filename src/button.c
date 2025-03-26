#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdio.h>

#include "../include/button.h"

Button createButton(int x, int y, int width, int height, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, int isPressed) {
    if (width <= 0 || height <= 0) {
        printf("Error: invalid button dimensions (%d x %d)\n", width, height);
        return (Button){0};
    }

    Button button = {x, y, width, height, color, hoverColor, clickColor, isPressed};

    printf("createButton success\n");

    return button;
}

void renderButton(Button *btn, SDL_Renderer *renderer) {
    SDL_Rect rect = {btn->x, btn->y, btn->width, btn->height};
    SDL_RenderDrawRect(renderer, &rect);

    if (btn->isPressed == 1) {
        SDL_SetRenderDrawColor(renderer, btn->clickColor.r, btn->clickColor.g, btn->clickColor.b, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, btn->color.r, btn->color.g, btn->color.b, 255);
    }

    SDL_RenderFillRect(renderer, &rect);
}