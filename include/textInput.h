#ifndef TEXTINPUT_H
#define TEXTINPUT_H

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
    int isSelected;
    int isHovered;
    SDL_Color color, hoverColor, clickColor, fontColor;
    int fontSize;
    char *text;
} TextInput;

EXPORT TextInput createTextInput(int x, int y, int width, int height, int isSelected, int isHovered, SDL_Color color, SDL_Color hoverColor, SDL_Color clickColor, SDL_Color fontColor, int fontSize, char *text);

EXPORT void handleTextInputEvent(TextInput *txtInpt, const SDL_Event event, char *textBuffer, size_t maxLen);

EXPORT void renderTextInput(TextInput *txtInpt, SDL_Renderer *renderer);

#endif