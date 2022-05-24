#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "../Game/game.h"

typedef struct{
    char *textureName;
    SDL_Texture *texture;
    int frameWidth;
    int frameHeight;
} turret_base;

typedef struct{
    char *textureName;
    SDL_Texture *texture;
    int nOfFrames;
    int currentFrame;
    int fireFrame;
    char *animationId;
    int frameWidth;
    int frameHeight;
} turret_canon;

typedef struct{
    char* texref;
    turret_base base;
    turret_canon canon;
    int delay;
    int range;
    char *projectileName;
    float maxRotationSpeed;
    float maxRotationAcceleration;
} turret_state;

typedef struct{
    char** name;
    int id;
    float rotation;
    int x;
    int y;
    int width;
    int height;
    bool turretLock;
    turret_state *currentState;
    list *states;
} turret;

typedef struct{
    char *turretId;
    int x;
    int y;
    int width;
    int height;
    int radius;
    SDL_Texture *thumbnail;
    SDL_Texture *allowed;
    SDL_Texture *forbidden;
    char **name;
} turretSelection;

GameObject *newGameObject_Turret(Game *GAME, char *turretFileName, int xpos, int ypos);
list *generateTurretsSelection(Game *GAME);