#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"

#include "../include/text.h"

TextBox createTextBox(int x, int y, int width, int height, SDL_Color color, int fontSize, char *text) {
    if (width <= 0 || height <= 0) {
        printf("Error: invalid text box dimensions (%d x %d)\n", width, height);
        return (TextBox){0};
    }

    TextBox textBox = {x, y, width, height, color, fontSize, NULL};

    textBox.text = malloc(strlen(text) + 1);
    if (!textBox.text) {
        printf("Error: failed to allocate memory for text\n");
        return (TextBox){0};
    }

    strcpy(textBox.text, text);

    printf("createTextBox success\n");

    return textBox;
}

void renderTextBox(TextBox *textBox, SDL_Renderer *renderer) {
    if (!textBox || !textBox->text || !renderer) return;

    TTF_Font *Font = TTF_OpenFont("./fonts/font.ttf", textBox->fontSize);
    if (!Font) {
        printf("Error: failed to load font\n");
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Solid(Font, textBox->text, textBox->color);
    if (!surface) {
        printf("Error: failed to create text surface\n");
        TTF_CloseFont(Font);
        return;
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surface);
    if (!message) {
        printf("Error: failed to create text texture\n");
    } else {
        SDL_Rect rect = {textBox->x, textBox->y, textBox->width, textBox->height};
        SDL_RenderCopy(renderer, message, NULL, &rect);
    }
}