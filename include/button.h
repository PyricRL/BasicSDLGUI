#ifndef BUTTON_H
#define BUTTON_H

typedef struct {
    int x, y;
    int width, height;
    SDL_Color color, hoverColor, clickColor;
    int isPressed;
} Button;

void renderButton(Button *btn, SDL_Renderer *renderer);

Button createButton(int x, int y, int width, int height, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, int isPressed);

#endif