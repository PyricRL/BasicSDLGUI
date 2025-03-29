#ifndef RADIOBUTTONMANAGER_H
#define RADIOBUTTONMANAGER_H

#define MAX_RADIOBUTTONS 10

#include "../include/radioButton.h"

typedef struct {
    int id;
    int selectedRadioButton;
    int buttonCount;
    RadioButton *buttons[MAX_RADIOBUTTONS];
} RadioButtonGroup;

RadioButtonGroup createRadioButtonGroup(int id, int selectedRadioButton);

void addRadioButtonToGroup(RadioButtonGroup *group, RadioButton *btn);

void handleRadioButtonEvent(RadioButtonGroup *group, const SDL_Event event);


#endif