#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL_ttf.h"

#include "../include/radioButtonManager.h"
#include "../include/radioButton.h"

/* 
* some sort of structure which can have an id (for a group identifier),
* holds an index of which button is selected
*/

EXPORT RadioButtonGroup createRadioButtonGroup(int id, int selectedRadioButton) {
    RadioButtonGroup group = {id, selectedRadioButton, 0};

    printf("createRadioButtonGroup success\n");

    return group;
}

EXPORT void addRadioButtonToGroup(RadioButtonGroup *group, RadioButton *btn) {
    if (group->buttonCount < MAX_RADIOBUTTONS) {
        group->buttons[group->buttonCount] = btn;
        group->buttonCount++;
    } else {
        printf("Error: Cannot add more radio buttons, maximum limit reached.\n");
    }
}

EXPORT void handleRadioButtonEvent(RadioButtonGroup *group, const SDL_Event event) {
    int mx = event.button.x;
    int my = event.button.y;

    for (int i = 0; i < group->buttonCount; i++) {
        RadioButton *btn = group->buttons[i];

        if (mx >= btn->x && mx <= (btn->x + btn->width) && my >= btn->y && my <= (btn->y + btn->height))
        {
            if (event.type == SDL_MOUSEBUTTONUP) {
                group->selectedRadioButton = i;
            }
            btn->isHovered = 1;
        } else {
            btn->isHovered = 0;
        }
    }
    
    for (int i = 0; i < group->buttonCount; i++) {
        group->buttons[i]->isSelected = (i == group->selectedRadioButton);;
    }
}