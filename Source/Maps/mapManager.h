#pragma once

#include "../List/SmartList.h"
#include "./mapDataManagement.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
    char *id;
    char *name;
    char *description;
    SDL_Texture *texture;
} mapPreview;

typedef struct
{
    map *currentMap;
    void (*loadMap)(const char *id, const int width, const int height, float *progress);
    void (*unloadMap)(void);
    void (*render)(void);
    void (*updatePreviews)(void);
    list *previews;
    void *parent;
} mapManager;

mapManager *initMapManager(void *game);