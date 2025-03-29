#ifndef RADIOBUTTONMANAGER_H
#define RADIOBUTTONMANAGER_H

#ifdef _WIN32
    #ifdef BUILDDLL
        #define EXPORT __declspec(dllexport)
    #else
        #define EXPORT __declspec(dllimport)
    #endif
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

#define MAX_RADIOBUTTONS 10

#include "../include/radioButton.h"

typedef struct {
    int id;
    int selectedRadioButton;
    int buttonCount;
    RadioButton *buttons[MAX_RADIOBUTTONS];
} RadioButtonGroup;

EXPORT RadioButtonGroup createRadioButtonGroup(int id, int selectedRadioButton);

EXPORT void addRadioButtonToGroup(RadioButtonGroup *group, RadioButton *btn);

EXPORT void handleRadioButtonEvent(RadioButtonGroup *group, const SDL_Event event);


#endif