#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Game/game.h"

#ifndef ROBOT_H
#define ROBOT_H

typedef struct{
    char *textureName;
    SDL_Texture *texture;
    int nOfFrames;
    int currentFrame;
} robot_walk;

typedef struct{
    char* name;
    char* texref;
    int id;
    float rotation;
    float x;
    float y;
    int width;
    int height;
    float speedx;
    float speedy;
    int life;
    int shield;
    int maxShield;
    int delay;
    int range;
    bool isFriendly;
    robot_walk walk;
    char *projectileName;
} robot;

GameObject *newGameObject_Robot(Game *GAME, char *robotFileName, int xpos, int ypos);

#endif