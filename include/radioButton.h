#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

typedef struct RadioButtonManager RadioButtonManager;

typedef struct {
    int x, y;
    int width, height;
    int isSelected;
    int isHovered;
    int groupID;
    SDL_Color color, hoverColor, clickColor;
    RadioButtonManager *manager;
} RadioButton;

void handleRadioButtonEvent(RadioButton *btn, const SDL_Event event);

void renderRadioButton(RadioButton *btn, SDL_Renderer *renderer);

#endif