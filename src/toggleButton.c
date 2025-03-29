#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"

#include "../include/toggleButton.h"

TTF_Font *toggleButtonFont = NULL;

EXPORT ToggleButton createToggleButton(int x, int y, int width, int height, int isToggled, int isHovered, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, SDL_Color fontColor, int fontSize, char *text) {
    toggleButtonFont = TTF_OpenFont("./fonts/font.ttf", fontSize);
    if (toggleButtonFont == NULL) {
        printf("Error: failed to load font");
        return (ToggleButton){0};
    }

    if (width <= 0 || height <= 0) {
        printf("Error: invalid toggle button dimensions (%d x %d)\n", width, height);
        return (ToggleButton){0};
    }

    if (text == NULL) {
        text = " ";
    }

    ToggleButton button = {x, y, width, height, isToggled, isHovered, color, hoverColor, clickColor, fontColor, fontSize, text};

    button.text = malloc(strlen(text) + 1);
    if (!button.text) {
        printf("Error: failed to allocate memory for text in toggle button\n");
        return (ToggleButton){0};
    }

    strcpy(button.text, text);

    printf("createToggleButton success\n");

    return button;
}

EXPORT void handleToggleButtonEvent(ToggleButton *btn, const SDL_Event event) {
    int mx = event.button.x;
    int my = event.button.y;
    if (mx >= btn->x && mx <= (btn->x + btn->width) && my >= btn->y && my <= (btn->y + btn->height))
    {
        if (event.type == SDL_MOUSEBUTTONUP) {
            btn->isToggled = !btn->isToggled;
        }
        btn->isHovered = 1;
    } else {
        btn->isHovered = 0;
    }
}

EXPORT void renderToggleButton(ToggleButton *btn, SDL_Renderer *renderer) {
    /* Draw button portion of button */
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

    /* Draw text portion of button */
    if (!btn || !btn->text || !renderer) return;

    if (!toggleButtonFont) {
        printf("Error: failed to load font in toggleButton\n");
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(toggleButtonFont, btn->text, btn->fontColor);
    if (!surface) {
        printf("Error: failed to create text surface in toggleButton\n");
        TTF_CloseFont(toggleButtonFont);
        return;
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surface);
    if (!message) {
        printf("Error: failed to create text texture in toggleButton\n");
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect textRect = {btn->x, btn->y, btn->width, btn->height};
    SDL_RenderCopy(renderer, message, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}