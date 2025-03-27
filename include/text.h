#ifndef TEXT_H
#define TEXT_H

typedef struct {
    int x, y;
    int width, height;
    SDL_Color color;
    int fontSize;
    char *text;
} TextBox;

TextBox createTextBox(int x, int y, int width, int height, SDL_Color color, int fontSize, char *text);

void renderTextBox(TextBox *textBox, SDL_Renderer *renderer);

#endif