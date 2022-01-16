#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct
{
    void (*getTexture)(void);
    void (*update)(void);
    void (*render)(void);
    void (*clean)(void);
    bool (*isRunning)(void);
    SDL_Window *window;
    SDL_Renderer *renderer;
} textureManager;