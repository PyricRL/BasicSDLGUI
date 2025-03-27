#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

typedef struct {
    int x, y;
    int width, height;
    int isToggled;
    int isHovered;
    SDL_Color color, hoverColor, clickColor, fontColor;
    int fontSize;
    char *text;
} ToggleButton;

ToggleButton createToggleButton(int x, int y, int width, int height, int isToggled, int isHovered, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, SDL_Color fontColor, int fontSize, char *text);

void handleToggleButtonEvent(ToggleButton *btn, const SDL_Event event);

void renderToggleButton(ToggleButton *btn, SDL_Renderer *renderer);

#endif