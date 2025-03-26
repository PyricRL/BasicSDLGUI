#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"

#include "../include/button.h"

TTF_Font *Font;

Button createButton(int x, int y, int width, int height, int isPressed, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, SDL_Color fontColor, int fontSize, char *text) {
    Font = TTF_OpenFont("./fonts/font.ttf", fontSize);
    if (Font == NULL) {
        printf("Error: failed to load font");
        return (Button){0};
    }

    if (width <= 0 || height <= 0) {
        printf("Error: invalid button dimensions (%d x %d)\n", width, height);
        return (Button){0};
    }

    if (text == NULL) {
        text = "";
    }

    Button button = {x, y, width, height, isPressed, color, hoverColor, clickColor, fontColor, fontSize, NULL};

    button.text = malloc(strlen(text) + 1);
    if (!button.text) {
        printf("Error: failed to allocate memory for text in button\n");
        return (Button){0};
    }

    strcpy(button.text, text);

    printf("createButton success\n");

    return button;
}

void renderButton(Button *btn, SDL_Renderer *renderer) {
    /* Draw button portion of button */
    SDL_Rect buttonRect = {btn->x, btn->y, btn->width, btn->height};
    SDL_RenderDrawRect(renderer, &buttonRect);

    if (btn->isPressed == 1) {
        SDL_SetRenderDrawColor(renderer, btn->clickColor.r, btn->clickColor.g, btn->clickColor.b, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, btn->color.r, btn->color.g, btn->color.b, 255);
    }

    SDL_RenderFillRect(renderer, &buttonRect);

    /* Draw text portion of button */
    if (!btn || !btn->text || !renderer) return;

    if (!Font) {
        printf("Error: failed to load font\n");
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(Font, btn->text, btn->fontColor);
    if (!surface) {
        printf("Error: failed to create text surface\n");
        TTF_CloseFont(Font);
        return;
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surface);
    if (!message) {
        printf("Error: failed to create text texture\n");
        SDL_FreeSurface(surface);
    }
    
    SDL_Rect textRect = {btn->x, btn->y, btn->width, btn->height};
    SDL_RenderCopy(renderer, message, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}