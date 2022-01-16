#include <SDL2/SDL.h>
#include <stdio.h>
#include <stlib.h>
#include <time.h>
#include "textureManager.h"

typedef struct
{
    int pv;
    int pvMax;
    int shield;
    int shieldMax;
} Enemy;