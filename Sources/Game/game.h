#include <SDL2/SDL.h>
#include <stdio.h>
#include <stlib.h>
#include <time.h>

typedef struct
{
    void (*handleEvents)(void);
    void (*update)(void);
    void (*render)(void);
    void (*clean)(void);
    bool (*isRunning)(void);
    SDL_Window *window;
    SDL_Renderer *renderer;
} Game;

Game *initGame(const char* title, int width, int height, bool fullscreen);