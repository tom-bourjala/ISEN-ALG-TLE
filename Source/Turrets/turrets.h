#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../Game/game.h"

typedef struct{
    char *textureName;
    SDL_Texture *texture;
} turret_base;

typedef struct{
    char *textureName;
    SDL_Texture *texture;
} turret_support;

typedef struct{
    char *textureName;
    SDL_Texture *texture;
    int nOfFrames;
    int currentFrame;
    char *animationId;
} turret_canon;

typedef struct{
    char** name;
    int id;
    char* texref;
    float rotation;
    float maxRotationSpeed;
    float maxRotationAcceleration;
    int x;
    int y;
    int width;
    int height;
    int delay;
    int range;
    char *projectileName;
    turret_base base;
    turret_support support;
    turret_canon canon;
} turret;

typedef struct{
    char *turretId;
    int x;
    int y;
    int width;
    int height;
    SDL_Texture *thumbnail;
    SDL_Texture *allowed;
    SDL_Texture *forbidden;
    char **name;
} turretSelection;

GameObject *newGameObject_Turret(Game *GAME, char *turretFileName, int xpos, int ypos);
list *generateTurretsSelection(Game *GAME);