#include <SDL2/SDL.h>
#include <stdio.h>
#include <stlib.h>
#include <time.h>
#include "textureManager.h"

typedef struct
{
    void (*handleEvents)(void);
    void (*update)(void);
    void (*render)(void);
    void (*clean)(void);
    bool (*isRunning)(void);
    SDL_Window *window;
    SDL_Renderer *renderer;
    textureManager *textureManager;
} Enemy;