#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../Game/game.h"
#include "./UI_loading.h"

static SDL_Thread *thread = NULL;
static float *progress = NULL;
static float *text = NULL;
static Game *game = NULL;

static int loadingThread(void *data){
    while(game->isRunning){
        //render loading screen
    }
    return 0;
}

void launchLoading(void *GAME, float *loadingProgress, char *loadingText){
    game = GAME;
    progress = loadingProgress;
    text = loadingText;
    game->menu = UI_initMenu(GAME);
    //Create menu UI
    thread = SDL_CreateThread(loadingThread, "Loading Thread", NULL);
}

void endLoading(void *GAME){
    //free menu UI
    SDL_KillThread(thread);
}