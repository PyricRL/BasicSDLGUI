#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#ifdef _WIN32
    #ifdef BUILDDLL
        #define EXPORT __declspec(dllexport)
    #else
        #define EXPORT __declspec(dllimport)
    #endif
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

typedef struct RadioButtonManager RadioButtonManager;

typedef struct {
    int x, y;
    int width, height;
    int isSelected;
    int isHovered;
    SDL_Color color, hoverColor, clickColor;
} RadioButton;

EXPORT RadioButton createRadioButton(int x, int y, int width, int height, int isSelected, int isHovered, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor);

EXPORT void renderRadioButton(RadioButton *btn, SDL_Renderer *renderer);

#endif