#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

typedef struct RadioButtonManager RadioButtonManager;

typedef struct {
    int x, y;
    int width, height;
    int isSelected;
    int isHovered;
    SDL_Color color, hoverColor, clickColor;
} RadioButton;

RadioButton createRadioButton(int x, int y, int width, int height, int isSelected, int isHovered, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor);

void renderRadioButton(RadioButton *btn, SDL_Renderer *renderer);

#endif