#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "rendererAddons.h"
#include "../Turrets/turrets.h"
#include "../Robots/robots.h"

static Game *GAME = NULL;

void handleEvents(){
    SDL_Event event;
    SDL_GetMouseState(&GAME->mouseX, &GAME->mouseY);
    SDL_GetWindowSize(GAME->window, &GAME->winWidth, &GAME->winHeight);
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT)
                    GAME->menu->handleEvent(event.button.type == SDL_MOUSEBUTTONDOWN);
                break;
            case SDL_QUIT:
                GAME->isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_F12:
                        GAME->key_debug++;
                        if(GAME->key_debug==DEBUG_EL) GAME->key_debug = DEBUG_NULL;
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void updateGameObject(void *object){
    ((GameObject*)object)->update(object);
}

void updateAnimation(void *targetAnim){
    ((animation*)targetAnim)->update(targetAnim);
}

void update(){
    GAME->currentCursor = GAME->cursorArrow;
    forEach(GAME->gameObjects, updateGameObject);
    forEach(GAME->animationManager->animList, updateAnimation);
    GAME->projectileManager->updateProjectiles();
    GAME->projectileManager->applyHits();
    GAME->menu->update();
    SDL_SetCursor(GAME->currentCursor);
}

void renderGameObject(void *object){
    ((GameObject*)object)->render(object);
}

void render(){
    SDL_SetRenderDrawColor(GAME->renderer, 55, 55, 55, 255);
    SDL_RenderClear(GAME->renderer);

    //Render MAP
    if(GAME->mapManager->currentMap) GAME->mapManager->render();

    //Render EFFECTS

    //Render OBJECTS
    forEach(GAME->gameObjects, renderGameObject);
    GAME->projectileManager->renderProjectiles();

    //Render UI
    if(GAME->menu) GAME->menu->render();

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
    GAME->projectileManager->empty();
    GAME->mapManager->unloadMap();
    GAME->languageManager->clear();
    GAME->menu->clear();
    forEach(GAME->animationManager->animList, freeAnimation);
    freeList(GAME->animationManager->animList);
    SDL_DestroyRenderer(GAME->renderer);
    SDL_DestroyWindow(GAME->window);
    IMG_Quit();
    SDL_FreeCursor(GAME->cursorArrow);
    SDL_FreeCursor(GAME->cursorHand);
    SDL_Quit();
    printf("SDL Cleaned...\n");
    forEach(GAME->gameObjects, deleteGameObject);
    freeList(GAME->gameObjects);
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
        if(TTF_Init()) printf("\033[1;31mTTF INIT: %s\033[0m\n", TTF_GetError());
    } else {
        GAME->isRunning = false;
        printf("\033[1;31mSDL Subsystems Initialising FAILED : %s\033[0m\n", SDL_GetError());
    }
    GAME->mouseX = 0;
    GAME->mouseY = 0;
    GAME->handleEvents = handleEvents;
    GAME->update = update;
    GAME->render = render;
    GAME->clean = clean;
    GAME->textureManager = initTexManager(GAME->renderer);
    GAME->animationManager = initAnimManager();
    GAME->projectileManager = initProjectileManager();
    GAME->mapManager = initMapManager(GAME);
    GAME->languageManager = initLanguageManager();
    UI_initMainMenu(GAME);
    GAME->gameObjects = newList(COMPARE_PTR);
    GAME->key_debug = DEBUG_NULL;
    GAME->status = GS_LoadingMainMenu;
    GAME->cursorHand = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    GAME->cursorArrow = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
    GAME->currentCursor = GAME->cursorArrow;
    GAME->winWidth = width;
    GAME->winWidth = height;
    return GAME;
}