#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "../Turrets/turrets.h"


Game *GAME = NULL;

void handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        GAME->isRunning = false;
        break;
    
    default:
        break;
    }
}

void update(){

}

void renderGameObject(void *object){
    ((GameObject*)object)->render(object);
}

void render(){
    SDL_RenderClear(GAME->renderer);
    //Render MAP
    //Render EFFECTS
    //Render OBJECTS
    forEach(GAME->gameObjects, renderGameObject);
    //Render UI
    SDL_RenderPresent(GAME->renderer);
}

void clean(){
    GAME->textureManager->empty();
    SDL_DestroyWindow(GAME->window);
    SDL_DestroyRenderer(GAME->renderer);
    SDL_Quit();
    printf("SDL Cleaned...\n");
    free(GAME);
}


Game *initGame(const char* title, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen) flags = SDL_WINDOW_FULLSCREEN;
    GAME = malloc(sizeof(Game));
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        printf("SDL Subsystems Initialised...\n");
        GAME->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
        if(GAME->window) printf("Window Created...\n");
        GAME->renderer = SDL_CreateRenderer(GAME->window, -1, 0);
        if(GAME->renderer) printf("Renderer Created...\n");
        GAME->isRunning = true;
    } else GAME->isRunning = false;
    GAME->handleEvents = handleEvents;
    GAME->update = update;
    GAME->render = render;
    GAME->clean = clean;
    GAME->textureManager = initTexManager(GAME->renderer);
    GAME->gameObjects = newList(COMPARE_PTR);
    appendInList(GAME->gameObjects, newGameObject_Turret(*GAME, "debug.turret", 200, 200));
    return GAME;
}