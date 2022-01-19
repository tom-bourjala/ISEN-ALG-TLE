#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "../Turrets/turrets.h"
#include "../Robots/robots.h"



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

void updateGameObject(void *object){
    ((GameObject*)object)->update(object);
}

void updateAnimation(void *targetAnim){
    ((animation*)targetAnim)->update(targetAnim);
}

void update(){
    forEach(GAME->gameObjects, updateGameObject);
    forEach(GAME->animationManager->animList, updateAnimation);
}

void renderGameObject(void *object){
    ((GameObject*)object)->render(object);
}

void render(){
    SDL_SetRenderDrawColor(GAME->renderer, 55, 55, 55, 255);
    SDL_RenderClear(GAME->renderer);
    //Render MAP
    //Render EFFECTS
    //Render OBJECTS
    forEach(GAME->gameObjects, renderGameObject);
    //Render UI
    SDL_RenderPresent(GAME->renderer);
}

void deleteGameObject(void *object){
    ((GameObject*)object)->delete(object);
}

void freeAnimation(void *animationToKill){
    animation* this = animationToKill;
    this->manager->killAnim(this->id);
}

void clean(){
    GAME->textureManager->empty();
    forEach(GAME->animationManager->animList, freeAnimation);
    emptyList(GAME->animationManager->animList);
    free(GAME->animationManager->animList);
    SDL_DestroyRenderer(GAME->renderer);
    SDL_DestroyWindow(GAME->window);
    IMG_Quit();
    SDL_Quit();
    printf("SDL Cleaned...\n");
    forEach(GAME->gameObjects, deleteGameObject);
    emptyList(GAME->gameObjects);
    free(GAME->gameObjects);
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
        else printf("\033[1;31mFailed to create window : %s\033[0m\n", SDL_GetError());
        GAME->renderer = SDL_CreateRenderer(GAME->window, -1, 0);
        if(GAME->renderer) printf("Renderer Created...\n");
        else printf("\033[1;31mFailed to create renderer : %s\033[0m\n", SDL_GetError());
        GAME->isRunning = true;
        if(!IMG_Init(IMG_INIT_PNG)) printf("\033[1;31mIMG INIT: %s\033[0m\n", IMG_GetError());
    } else {
        GAME->isRunning = false;
        printf("\033[1;31mSDL Subsystems Initialising FAILED : %s\033[0m\n", SDL_GetError());
    } 
    GAME->handleEvents = handleEvents;
    GAME->update = update;
    GAME->render = render;
    GAME->clean = clean;
    GAME->textureManager = initTexManager(GAME->renderer);
    GAME->animationManager = initAnimManager();
    GAME->gameObjects = newList(COMPARE_PTR);
    appendInList(GAME->gameObjects, newGameObject_Turret(GAME, "debug.turret", 100, 100));
    appendInList(GAME->gameObjects, newGameObject_Robot(GAME, "debug.robot", 200, 200));
    return GAME;
}

weaponType getWeaponTypeFromString(char *fileParamString){
    if(!strcmp("BALLISTIC", fileParamString)) return BALLISTIC;
    if(!strcmp("PLASMA", fileParamString)) return PLASMA;
    if(!strcmp("EXPLOSIVE", fileParamString)) return EXPLOSIVE;
    return 0;
}