#include "camera.h"

static Game *GAME = NULL;

void initCamera(Game *game)
{
    GAME = game;
}

void cameraRender(SDL_Texture *tex, SDL_Rect dest){
    dest.x -= GAME->cameraX;
    dest.y -= GAME->cameraY;
    SDL_RenderCopy(GAME->renderer, tex, NULL, &dest);
}

void cameraRenderFrame(SDL_Texture *tex, SDL_Rect dest, int frame){
    int frameWidth, frameHeight;
    SDL_QueryTexture(tex, NULL, NULL, &frameWidth, &frameHeight);
    dest.x -= GAME->cameraX;
    dest.y -= GAME->cameraY;
    SDL_Rect src = {frame * frameHeight, 0, frameHeight, frameHeight};
    SDL_RenderCopy(GAME->renderer, tex, &src, &dest);
}

void cameraRenderEx(SDL_Texture *tex, SDL_Rect dest, int frame, float angle, bool hFlip, bool vFlip){
    int frameWidth, frameHeight;
    SDL_QueryTexture(tex, NULL, NULL, &frameWidth, &frameHeight);
    SDL_Rect src = {frame * frameHeight, 0, frameHeight, frameHeight};
    dest.x -= GAME->cameraX;
    dest.y -= GAME->cameraY;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if(hFlip) flip = SDL_FLIP_HORIZONTAL;
    if(vFlip){
        if(hFlip) flip =  SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
        else flip = SDL_FLIP_VERTICAL;
    }
    SDL_RenderCopyEx(GAME->renderer, tex, &src, &dest, angle, NULL, flip);
}