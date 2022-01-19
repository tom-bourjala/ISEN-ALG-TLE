#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Game/game.h"

typedef struct{
    int delay;
    int range;
    int projectileSpeed;
    int projectileDamage;
    int x;
    int y;
    weaponType type;
} robot_weapon;

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
    int x;
    int y;
    int speedx;
    int speedy;
    int life;
    int shield;
    int maxShield;
    bool isFriendly;
    robot_walk walk;
    robot_weapon weapon;
} robot;

GameObject *newGameObject_Robot(Game *GAME, char *robotFileName, int xpos, int ypos);