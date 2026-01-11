#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

/* Forward declaration */
typedef struct Emulator Emulator_t;

typedef struct display
{
    SDL_Window *window;
    SDL_Renderer *renderer;

} display_t;


display_t *initialize_display();

void cleanup_display(display_t *display);

#endif // DISPLAY_H