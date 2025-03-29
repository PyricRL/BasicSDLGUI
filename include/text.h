#ifndef TEXT_H
#define TEXT_H

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
    SDL_Color color;
    int fontSize;
    char *text;
} TextBox;

EXPORT TextBox createTextBox(int x, int y, int width, int height, SDL_Color color, int fontSize, char *text);

EXPORT void renderTextBox(TextBox *textBox, SDL_Renderer *renderer);

#endif