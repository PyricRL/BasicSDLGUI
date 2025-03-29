#ifndef TOGGLEBUTTON_H
#define TOGGLEBUTTON_H

#ifdef _WIN32
    #ifdef BUILDDLL
        #define EXPORT __declspec(dllexport)
    #else
        #define EXPORT __declspec(dllimport)
    #endif
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

typedef struct {
    int x, y;
    int width, height;
    int isToggled;
    int isHovered;
    SDL_Color color, hoverColor, clickColor, fontColor;
    int fontSize;
    char *text;
} ToggleButton;

EXPORT ToggleButton createToggleButton(int x, int y, int width, int height, int isToggled, int isHovered, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, SDL_Color fontColor, int fontSize, char *text);

EXPORT void handleToggleButtonEvent(ToggleButton *btn, const SDL_Event event);

EXPORT void renderToggleButton(ToggleButton *btn, SDL_Renderer *renderer);

#endif