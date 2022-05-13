#include "turretUsher.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "turrets.h"
#include "../Game/selection.h"
#include "../Game/rendererAddons.h"

static bool isPlacementValid(Game *game, SDL_Rect *dest){
    bool valid = true;
    void checkTurretOverlap(void *self){
        GameObject *obj = self;
        if(obj->type == GOT_Turret){
            turret *this = obj->actor;
            SDL_Rect turretRect = {this->x, this->y, this->width, this->height};
            if(SDL_HasIntersection(&turretRect, dest)){
                valid = false;
            }
        }
    }
    forEach(game->gameObjects, checkTurretOverlap);
    if(!valid) return false;
    map_dataGrid dataGrid = game->mapManager->currentMap->dataGrid;
    int x1 = dest->x;
    int y1 = dest->y;
    int x2 = dest->x + dest->w;
    int y2 = dest->y + dest->h;
    for(int y = y1; y < y2; y++){
        for(int x = x1; x < x2; x++){
            if(x < 0 || x >= dataGrid.w || y < 0 || y >= dataGrid.h) return false;
            if(dataGrid.grid[y][x].type != MCT_EMPTY) return false;
        }
    }
    return true;
}

SDL_Rect getTurretPlacement(Game *game, turretSelection *selection){
    //Get projected width and height
    SDL_Rect dest = {selection->x, selection->y, selection->width, selection->height};
    projectRectToCamera(&dest);
    dest = (SDL_Rect) {game->mouseX - (dest.w/2), game->mouseY - (dest.h/2), dest.w, dest.h};
    projectRectToCamera_inv(&dest);
    return dest;
}

void renderTurretSelection(Game *game){
    if(!game->selection) return;
    Selection *selection = game->selection;
    if(selection->type != SELECT_TURRET) return;
    turretSelection *turret = selection->selected.turretSelection;
    if(!turret) return;
    SDL_Rect dest = getTurretPlacement(game, turret);
    if(!isPlacementValid(game, &dest)) cameraRender(turret->forbidden, dest);
    else{
        cameraRender(turret->allowed, dest);
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 100);
        DrawCircle(game->renderer, dest.x+(dest.w/2), dest.y+(dest.h/2), turret->radius);
        SDL_SetRenderDrawColor(game->renderer, 43, 250, 250, 200);
        DrawCircle(game->renderer, dest.x+(dest.w/2), dest.y+(dest.h/2), turret->radius-1);
        DrawCircle(game->renderer, dest.x+(dest.w/2), dest.y+(dest.h/2), turret->radius-2);
        DrawCircle(game->renderer, dest.x+(dest.w/2), dest.y+(dest.h/2), turret->radius-3);
        SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 100);
        DrawCircle(game->renderer, dest.x+(dest.w/2), dest.y+(dest.h/2), turret->radius-4);
    }
}

void handleInputTurretSelection(Game *game, SDL_Event *event){
    Selection *selection = game->selection;
    if(selection->type != SELECT_TURRET) return;
    turretSelection *turret = selection->selected.turretSelection;
    switch (event->type)
    {
        case SDL_MOUSEBUTTONUP:
            if(event->button.button == SDL_BUTTON_LEFT && !game->cameraDragging){
                if(game->mouseY < game->winHeight - 200){
                    SDL_Rect dest = getTurretPlacement(game, turret);
                    if(isPlacementValid(game, &dest)){
                        newGameObject_Turret(game, turret->turretId, dest.x, dest.y);
                        free(selection);
                        game->selection = NULL;
                    }
                }
            }else{
                free(selection);
                game->selection = NULL;
            }
            break;
        default:
            break;
    }
}