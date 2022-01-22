#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "textureManager.h"
#include "animationManager.h"
#include "projectileManager.h"
#include "../List/SmartList.h"

#ifndef GAME_H
#define GAME_H

typedef struct
{
    void (*handleEvents)(void);
    void (*update)(void);
    void (*render)(void);
    void (*clean)(void);
    SDL_Window *window;
    SDL_Renderer *renderer;
    textureManager *textureManager;
    animationManager *animationManager;
    projectileManager *projectileManager;
    list *gameObjects;
    bool isRunning;
} Game;

Game *initGame(const char* title, int width, int height, bool fullscreen);

typedef struct GameObject GameObject;
typedef enum {GOT_Turret, GOT_Robot, GOT_Projectile, GOT_Effect} GameObjectType;

struct GameObject{
    void (*update)(void *self);
    void (*render)(void *self);
    void (*delete)(void *self);
    bool (*isAlive)(void *self);
    Game *game;
    GameObjectType type;
    void *actor;
};

typedef enum{BALLISTIC, PLASMA, EXPLOSIVE} weaponType;

#endif