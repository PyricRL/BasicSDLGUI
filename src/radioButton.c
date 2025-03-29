#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"

#include "../include/radioButton.h"
#include "../include/radioButtonManager.h"

RadioButton createRadioButton(int x, int y, int width, int height, int isSelected, int isHovered, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor) {
    if (width <= 0 || height <= 0) {
        printf("Error: invalid toggle button dimensions (%d x %d)\n", width, height);
        return (RadioButton){0};
    }

    RadioButton button = {x, y, width, height, isSelected, isHovered, color, hoverColor, clickColor};

    printf("createRadioButton success\n");

    return button;
}

void renderRadioButton(RadioButton *btn, SDL_Renderer *renderer) {
    SDL_Rect buttonRect = {btn->x, btn->y, btn->width, btn->height};

    if (btn->isSelected == 1) {
        SDL_SetRenderDrawColor(renderer, btn->clickColor.r, btn->clickColor.g, btn->clickColor.b, 255);
    } else if (btn->isHovered == 1) {
        SDL_SetRenderDrawColor(renderer, btn->hoverColor.r, btn->hoverColor.g, btn->hoverColor.b, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, btn->color.r, btn->color.g, btn->color.b, 255);
    }

    SDL_RenderDrawRect(renderer, &buttonRect);
    SDL_RenderFillRect(renderer, &buttonRect);
}