#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../List/SmartList.h"

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

typedef struct
{
    SDL_Texture* (*getTexture)(char* string);
    void (*empty)(void);
    list *texList;
} textureManager;

typedef struct
{
    char* name;
    SDL_Texture* texture;
} texture;

textureManager *initTexManager(SDL_Renderer *renderer);

#endif