#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include "game.h"
#include "../List/SmartList.h"

typedef struct{
    void (*delete)(void *self);
    int damage;
    float x;
    float y;
    weaponType type;
    GameObject *parent;
    GameObject *target;
} hit;

typedef struct
{
    void (*empty)(void);
    void (*newProjectile)(Game *GAME, char *projectileFileName, float xpos, float ypos, float rotation, GameObject *parent);
    list *projectiles;
    list *hits;
} projectileManager;

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
    int damage;
    int perforance;
    bool isFriendly;
    projectileRenderer projectileRenderer;
    projectileManager *manager;
    weaponType type;
    GameObject *parent;
} projectile;

typedef struct{
    char* texref;
    SDL_Texture *texture;
    int width;
    int height;
    int nOfFrames;
    int currentFrame;
    char *animationId;
} projectileRenderer;

projectileManager *initProjectileManager();