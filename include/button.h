#ifndef BUTTON_H
#define BUTTON_H

typedef struct {
    int x, y;
    int width, height;
    int isPressed;
    int isHovered;
    SDL_Color color, hoverColor, clickColor, fontColor;
    int fontSize;
    char *text;
} Button;

Button createButton(int x, int y, int width, int height, int isPressed, int isHovered, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, SDL_Color fontColor, int fontSize, char *text);

void handleButtonEvent(Button *btn, const SDL_Event event);

void renderButton(Button *btn, SDL_Renderer *renderer);

#endif