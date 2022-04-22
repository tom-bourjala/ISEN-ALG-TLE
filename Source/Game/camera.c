#include "camera.h"

static Game *GAME = NULL;

void initCamera(Game *game)
{
    GAME = game;
}

static void updateRectDest(SDL_Rect *dest){
    dest->x -= GAME->cameraX;
    dest->y -= GAME->cameraY;
    dest->x *= GAME->cameraScale;
    dest->y *= GAME->cameraScale;
    dest->w *= GAME->cameraScale;
    dest->h *= GAME->cameraScale;
}

void cameraRender(SDL_Texture *tex, SDL_Rect dest){
    updateRectDest(&dest);
    SDL_RenderCopy(GAME->renderer, tex, NULL, &dest);
}

void cameraRenderFrame(SDL_Texture *tex, SDL_Rect dest, int frame){
    int frameWidth, frameHeight;
    SDL_QueryTexture(tex, NULL, NULL, &frameWidth, &frameHeight);
    updateRectDest(&dest);
    SDL_Rect src = {frame * frameHeight, 0, frameHeight, frameHeight};
    SDL_RenderCopy(GAME->renderer, tex, &src, &dest);
}

void cameraRenderEx(SDL_Texture *tex, SDL_Rect dest, int frame, float angle, bool hFlip, bool vFlip){
    int frameWidth, frameHeight;
    SDL_QueryTexture(tex, NULL, NULL, &frameWidth, &frameHeight);
    updateRectDest(&dest);
    SDL_Rect src = {frame * frameHeight, 0, frameHeight, frameHeight};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(hFlip) flip = SDL_FLIP_HORIZONTAL;
    if(vFlip){
        if(hFlip) flip =  SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
        else flip = SDL_FLIP_VERTICAL;
    }
    SDL_RenderCopyEx(GAME->renderer, tex, &src, &dest, angle, NULL, flip);
}