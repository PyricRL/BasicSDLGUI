#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"

#include "../include/radioButton.h"
#include "../include/radioButtonManager.h"

RadioButton createRadioButton(int x, int y, int width, int height, int isSelected, int isHovered, int groupID, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, RadioButtonManager *manager) {
    if (width <= 0 || height <= 0) {
        printf("Error: invalid toggle button dimensions (%d x %d)\n", width, height);
        return (RadioButton){0};
    }

    RadioButton button = {x, y, width, height, isSelected, isHovered, color, hoverColor, clickColor, manager};

    printf("createRadioButton success\n");

    return button;
}

void handleRadioButtonEvent(RadioButton *btn, const SDL_Event event) {
    int mx = event.button.x;
    int my = event.button.y;
    if (mx >= btn->x && mx <= (btn->x + btn->width) && my >= btn->y && my <= (btn->y + btn->height))
    {
        if (!btn->isSelected) {
            updateRadioButtonGroup(btn->manager, btn);
        }
        btn->isHovered = 1;
    } else {
        btn->isHovered = 0;
    }
}

void renderRadioButton(RadioButton *btn, const SDL_Event event) {
    SDL_Rect buttonRect = {btn->x, btn->y, btn->width, btn->height};

    if (btn->isToggled == 1) {
        SDL_SetRenderDrawColor(renderer, btn->clickColor.r, btn->clickColor.g, btn->clickColor.b, 255);
    } else if (btn->isHovered == 1) {
        SDL_SetRenderDrawColor(renderer, btn->hoverColor.r, btn->hoverColor.g, btn->hoverColor.b, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, btn->color.r, btn->color.g, btn->color.b, 255);
    }

    SDL_RenderDrawRect(renderer, &buttonRect);
    SDL_RenderFillRect(renderer, &buttonRect);
}