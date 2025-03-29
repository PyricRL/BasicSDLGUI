#ifndef RADIOBUTTONMANAGER_H
#define RADIOBUTTONMANAGER_H

#include "radioButton.h"

#define MAX_RADIO_BUTTON 10

typedef struct {
    RadioButton *buttons[MAX_RADIO_BUTTON];
    int count;
} RadioButtonManager;


#endif