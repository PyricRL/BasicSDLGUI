#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"

#include "../include/button.h"

TTF_Font *buttonFont = NULL;

Button createButton(int x, int y, int width, int height, int isPressed, int isHovered, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, SDL_Color fontColor, int fontSize, char *text) {
    buttonFont = TTF_OpenFont("./fonts/font.ttf", fontSize);
    if (buttonFont == NULL) {
        printf("Error: failed to load font");
        return (Button){0};
    }

    if (width <= 0 || height <= 0) {
        printf("Error: invalid button dimensions (%d x %d)\n", width, height);
        return (Button){0};
    }

    if (text == NULL) {
        text = " ";
    }

    Button button = {x, y, width, height, isPressed, isHovered, color, hoverColor, clickColor, fontColor, fontSize, text};

    button.text = malloc(strlen(text) + 1);
    if (!button.text) {
        printf("Error: failed to allocate memory for text in button\n");
        return (Button){0};
    }

    strcpy(button.text, text);

    printf("createButton success\n");

    return button;
}

void handleButtonEvent(Button *btn, const SDL_Event event) {
    int mx = event.button.x;
    int my = event.button.y;
    if (mx >= btn->x && mx <= (btn->x + btn->width) && my >= btn->y && my <= (btn->y + btn->height))
    {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            btn->isPressed = 1;
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            btn->isPressed = 0;
        }
        btn->isHovered = 1;
    } else {
        btn->isHovered = 0;
    }
}

void renderButton(Button *btn, SDL_Renderer *renderer) {
    /* Draw button portion of button */
    SDL_Rect buttonRect = {btn->x, btn->y, btn->width, btn->height};

    if (btn->isPressed == 1) {
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

    if (!buttonFont) {
        printf("Error: failed to load font in button\n");
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(buttonFont, btn->text, btn->fontColor);
    if (!surface) {
        printf("Error: failed to create text surface in button\n");
        TTF_CloseFont(buttonFont);
        return;
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surface);
    if (!message) {
        printf("Error: failed to create text texture\n");
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect textRect = {btn->x, btn->y, btn->width, btn->height};
    SDL_RenderCopy(renderer, message, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}