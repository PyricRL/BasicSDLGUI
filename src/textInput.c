#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"

#include "../include/textInput.h"

TTF_Font *textInputFont = NULL;

TextInput createTextInput(int x, int y, int width, int height, int isSelected, int isHovered, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, SDL_Color fontColor, int fontSize, char *text) {
    textInputFont = TTF_OpenFont("./fonts/font.ttf", fontSize);
    if (textInputFont == NULL) {
        printf("Error: failed to load font in textInput");
        return (TextInput){0};
    }

    if (width <= 0 || height <= 0) {
        printf("Error: invalid textInput dimensions (%d x %d)\n", width, height);
        return (TextInput){0};
    }

    if (text == NULL) {
        text = "0";
    }

    TextInput textInput = {x, y, width, height, isSelected, isHovered, color, hoverColor, clickColor, fontColor, fontSize, text};

    textInput.text = malloc(strlen(text) + 1);
    if (!textInput.text) {
        printf("Error: failed to allocate memory for text in textInput\n");
        return (TextInput){0};
    }

    strcpy(textInput.text, text);

    printf("createTextInput success\n");

    return textInput;
}

void handleTextInputEvent(TextInput *txtInpt, const SDL_Event event, char *textBuffer, size_t maxLen) {
    int mx = event.button.x;
    int my = event.button.y;
    if (event.type == SDL_MOUSEBUTTONUP) {
        if (mx >= txtInpt->x && mx <= (txtInpt->x + txtInpt->width) && my >= txtInpt->y && my <= (txtInpt->y + txtInpt->height)) {
            txtInpt->isSelected = !txtInpt->isSelected;
        } else {
            txtInpt->isSelected = 0;
        }
    }

    if (event.type == SDL_MOUSEMOTION) {
        int mx = event.motion.x;
        int my = event.motion.y;
        txtInpt->isHovered = (mx >= txtInpt->x && mx <= (txtInpt->x + txtInpt->width) && my >= txtInpt->y && my <= (txtInpt->y + txtInpt->height));
    }

    if (event.type == SDL_TEXTINPUT && txtInpt->isSelected) {
        for (int i = 0; i < strlen(event.text.text); ++i) {
            if (isdigit(event.text.text[i])) {
                if (strlen(textBuffer) + 1 < maxLen) {
                    if ((strlen(textBuffer) == 1) && textBuffer[0] == '0') {
                        textBuffer[0] = event.text.text[i];
                    } else {
                        strncat(textBuffer, &event.text.text[i], 1);
                    }
                }
            }
        }
        txtInpt->text = textBuffer;
    }

    if (event.type == SDL_KEYDOWN && txtInpt->isSelected) {
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
            if (strlen(textBuffer) > 1) {
                textBuffer[strlen(textBuffer) - 1] = '\0';
            } else {
                textBuffer[0] = '0';
                textBuffer[1] = '\0';
            }
        }
    }
}

void renderTextInput(TextInput *txtInpt, SDL_Renderer *renderer) {
    /* Draw button portion of button */
    SDL_Rect textInputRect = {txtInpt->x, txtInpt->y, txtInpt->width, txtInpt->height};

    if (txtInpt->isSelected) {
        SDL_SetTextInputRect(&textInputRect);
        SDL_StartTextInput();
    } else {
        SDL_StopTextInput();
    }

    if (txtInpt->isSelected == 1) {
        SDL_SetRenderDrawColor(renderer, txtInpt->clickColor.r, txtInpt->clickColor.g, txtInpt->clickColor.b, 255);
    } else if (txtInpt->isHovered == 1) {
        SDL_SetRenderDrawColor(renderer, txtInpt->hoverColor.r, txtInpt->hoverColor.g, txtInpt->hoverColor.b, 255);
    } else {
        SDL_SetRenderDrawColor(renderer, txtInpt->color.r, txtInpt->color.g, txtInpt->color.b, 255);
    }

    SDL_RenderDrawRect(renderer, &textInputRect);

    SDL_RenderFillRect(renderer, &textInputRect);

    /* Draw text portion of button */
    if (!txtInpt || !txtInpt->text || !renderer) return;

    if (!textInputFont) {
        printf("Error: failed to load font in textInput\n");
        return;
    }

    SDL_Surface *surface = TTF_RenderText_Blended(textInputFont, txtInpt->text, txtInpt->fontColor);
    if (!surface) {
        printf("Error: failed to create text surface in textInput\n");
        TTF_CloseFont(textInputFont);
        return;
    }

    SDL_Texture *message = SDL_CreateTextureFromSurface(renderer, surface);
    if (!message) {
        printf("Error: failed to create text texture in textInput\n");
        SDL_FreeSurface(surface);
        return;
    }
    
    SDL_Rect textRect = {txtInpt->x, txtInpt->y, txtInpt->width, txtInpt->height};
    SDL_RenderCopy(renderer, message, NULL, &textRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(message);
}