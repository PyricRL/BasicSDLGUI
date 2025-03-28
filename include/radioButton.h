#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

typedef struct {
    int x, y;
    int width, height;
    int isSelected;
    int group;
    SDL_Color color, hoverColor, clickColor, fontColor;
} RadioButton;

#endif