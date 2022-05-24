#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../List/SmartList.h"

#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

typedef enum{BALLISTIC, PLASMA, EXPLOSIVE, LASER} weaponType;

typedef struct{
    void (*delete)(void *self);
    int damage;
    float x;
    float y;
    weaponType type;
    void *parent;
    void *target;
} hit;

typedef struct
{
    void (*empty)(void);
    void (*free)(void);
    void (*newProjectile)(void *GAME, char *projectileFileName, float xpos, float ypos, float rotation, void *parent, void *target);
    void (*newHit)(int damage, float x, float y, weaponType type, void *parent, void *target);
    void (*updateProjectiles)(void);
    void (*renderProjectiles)(void);
    void (*applyHits)(void);
    list *projectiles;
    list *hits;
} projectileManager;

typedef struct{
    char* texref;
    SDL_Texture *texture;
    int freamWidth;
    int freamHeight;
    int nOfFrames;
    int currentFrame;
    char *animationId;
} projectileRenderer;

typedef struct{
    void (*update)(void *self);
    void (*render)(void *self);
    void (*delete)(void *self);
    bool (*isAlive)(void *self);
    unsigned int id;
    float speedx;
    float speedy;
    float speed;
    float rotation;
    float x;
    float y;
    int width;
    int height;
    int damage;
    int perforance;
    bool isFriendly;
    projectileRenderer projectileRenderer;
    projectileManager *manager;
    weaponType type;
    void *target;
    void *parent;
} projectile;

projectileManager *initProjectileManager();
#endif