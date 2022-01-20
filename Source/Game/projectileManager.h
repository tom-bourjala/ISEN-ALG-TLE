#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "../List/SmartList.h"

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