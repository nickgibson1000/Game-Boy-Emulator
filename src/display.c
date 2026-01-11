#include "../include/display.h"

#define WINDOW_TITLE "Game"
#define WINDOW_HEIGHT 160
#define WINDOW_WIDTH 144



display_t *initialize_display()
{
    
    display_t *display = malloc(sizeof(display_t));
    if(display == NULL)
    {
        fprintf(stderr, "ERROR: Failed to intialize display \n");
        exit(-1);
    }


    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        fprintf(stderr, "Error initializing SDL %s\n", SDL_GetError());
        exit(-1);
    }

    display->window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    if (!display->window) {
        fprintf(stderr, "Error creating Window %s\n", SDL_GetError());
        exit(-1);
    }

    display->renderer = SDL_CreateRenderer(display->window, -1, 0);
    if (!display->renderer) {
        fprintf(stderr, "Error creating Renderer %s\n", SDL_GetError());
        exit(-1);
    }

    return display;
}


void cleanup_display(display_t *display)
{
    SDL_DestroyWindow(display->window);
    SDL_DestroyRenderer(display->renderer);
    SDL_Quit();
}