#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Game/game.h"

typedef struct{
    SDL_Texture *coreTex;
    SDL_Texture *shieldTex;
    int health;
    int maxHealth;
    int shield;
    int maxShield;
    int rechargeDelay;
    int rechargeDelayCounter;
    float rechargeRate;
    int radius;
    map_node *node;
} core;

GameObject *newGameObject_Core(Game *GAME, map_node *spawnNode, int maxHealth, int maxShield, int rechargeDelay, float rechargeRate);
void hitCore(GameObject *target, int damage);