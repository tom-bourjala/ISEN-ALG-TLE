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
    int seed;
    float rotation;
    float rotationCache;
    float x;
    float y;
    int width;
    int height;
    float speedx;
    float speedy;
    float maxSpeed;
    int life;
    int shield;
    int maxShield;
    int delay;
    int delayCounter;
    int range;
    int radius;
    bool isFriendly;
    robot_walk walk;
    map_node *targetNode;
    map_node *lastNode;
    char *projectileName;
} robot;

GameObject *newGameObject_Robot(Game *GAME, char *robotFileName, map_node *spawnNode, int seed);

#endif