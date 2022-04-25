#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

void initCamera(Game *game);
void cameraRender(SDL_Texture *tex, SDL_Rect dest);
void cameraRenderFrame(SDL_Texture *tex, SDL_Rect dest, int frame);
void cameraRenderEx(SDL_Texture *tex, SDL_Rect dest, int frame, float angle, bool hFlip, bool vFlip);
void cameraRenderExUnsquared(SDL_Texture *tex, SDL_Rect dest, int frame, int nOfFrames, float angle, bool hFlip, bool vFlip);