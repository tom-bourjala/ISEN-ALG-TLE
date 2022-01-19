#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "../List/SmartList.h"

typedef struct{
    float speedx;
    float speedy;
    float x;
    float y;
    int damage;
    weaponType type;
    GameObject *parent;
} projectile;