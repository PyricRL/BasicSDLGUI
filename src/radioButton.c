#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"

#include "../include/radioButton.h"

RadioButton createRadioButton(int x, int y, int width, int height, int isSelected, int group, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor) {
    if (width <= 0 || height <= 0) {
        printf("Error: invalid button dimensions (%d x %d)\n", width, height);
        return (RadioButton){0};
    }

    RadioButton button = {x, y, width, height, isSelected, group, color, hoverColor, clickColor};

    printf("radioButton success\n");

    return button;
}

void renderToggleButton(RadioButton *btn, SDL_Renderer *renderer) {
    SDL_Rect buttonRect = {btn->x, btn->y, btn->width, btn->height};


    SDL_RenderDrawRect(renderer, &buttonRect);
    SDL_RenderFillRect(renderer, &buttonRect);
}