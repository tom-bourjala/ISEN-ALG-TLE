#include <stdio.h>
#include <stdlib.h>
#include "../Game/game.h"

typedef struct{
    int delay;
    int range;
    int projectileSpeed;
    int projectileDamage;
    int x;
    int y;
    weaponType type;
} turret_weapon;

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
    char* name;
    int id;
    char* texref;
    float rotation;
    float maxRotationSpeed;
    float maxRotationAcceleration;
    int x;
    int y;
    int width;
    int height;
    turret_weapon weapon;
    turret_base base;
    turret_support support;
    turret_canon canon;
} turret;

GameObject *newGameObject_Turret(Game *GAME, char *turretFileName, int xpos, int ypos);