#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "game.h"

#ifndef RENDERADDONS_H
#define RENDERADDONS_H

void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);

typedef enum {DO_Hit} debugObjectType;

typedef struct{
    int x;
    int y;
    int TTL;
    debugObjectType type;
} debugObject;

GameObject *newGameObject_Debug(Game *GAME, int xpos, int ypos, int TTL, debugObjectType type);

void relativeRender(SDL_Texture *tex, int x, int y, int w, int h);
void relativeRenderFrame(SDL_Texture *tex, int x, int y, int w, int h, int frame);
void relativeRenderEx(SDL_Texture *tex, int x, int y, int w, int h, int frame, int angle, bool hFlip, bool vFlip);

#endif