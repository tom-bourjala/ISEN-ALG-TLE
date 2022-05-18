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

void projectRectToCamera(SDL_Rect *dest);
void projectRectToCamera_inv(SDL_Rect *dest);

void cameraCheckSize();
void cameraZoom(float zoom);
void cameraMove(int x, int y);
void cameraZoomAt(float zoom, int x, int y);

void cameraStartDrag();
void cameraDrag();
void cameraEndDrag();