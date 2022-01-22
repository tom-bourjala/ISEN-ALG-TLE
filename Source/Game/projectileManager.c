#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "../Robots/robots.h"
#include "../Turrets/turrets.h"
#include "projectileManager.h"
#include "game.h"

#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)
#define ABS(X)  ((X>=0)? X : -(x) ) 
#define ROUND(X)  (X>=0)? (int) (X + 0.5) : (int)-(ABS(X) +0.5)

typedef enum{P_TEX_REF, P_TEX_ANIM_FRAMES,P_WIDTH, P_HEIGHT, P_WEAPON_DAMAGE, P_WEAPON_SPEED, P_WEAPON_PERFORANCE, P_WEAPON_TYPE, P_NONE} projectileConfigFileParam;

projectileManager *PROJECTILE_MANAGER = NULL;


void hitDelete(void *self){
    hit *this = self;
    deleteInList(PROJECTILE_MANAGER->hits, this);
    free(this);
}

void newHit(int damage, float x, float y, weaponType type, GameObject *parent, GameObject *target){
    hit *createdHit = malloc(sizeof(hit));
    createdHit->delete = hitDelete;
    createdHit->parent = parent;
    createdHit->target = target;
    createdHit->damage = damage;
    createdHit->x = x;
    createdHit->y = y;
    createdHit->parent = parent;
    createdHit->delete = hitDelete;
    pushInList(PROJECTILE_MANAGER->hits, createdHit);
}

projectileConfigFileParam getProjectileConfigFileParamFromString(char *fileParamString){
    if(!strcmp("TEX_REF", fileParamString)) return P_TEX_REF;
    if(!strcmp("TEX_ANIM_FRAMES", fileParamString)) return P_TEX_ANIM_FRAMES;
    if(!strcmp("WEAPON_DAMAGE", fileParamString)) return P_WEAPON_DAMAGE;
    if(!strcmp("WEAPON_SPEED", fileParamString)) return P_WEAPON_SPEED;
    if(!strcmp("WEAPON_PERFORANCE", fileParamString)) return P_WEAPON_PERFORANCE;
    if(!strcmp("WIDTH", fileParamString)) return P_WIDTH;
    if(!strcmp("HEIGHT", fileParamString)) return P_HEIGHT;
    if(!strcmp("WEAPON_TYPE", fileParamString)) return P_WEAPON_TYPE;
    return P_NONE;
}

weaponType getWeaponTypeFromString(char *fileParamString){
    if(!strcmp("BALLISTIC", fileParamString)) return BALLISTIC;
    if(!strcmp("PLASMA", fileParamString)) return PLASMA;
    if(!strcmp("EXPLOSIVE", fileParamString)) return EXPLOSIVE;
    return 0;
}

projectile *newProjectile(Game GAME,char *projectileFileName, float xpos, float ypos, float rotation, bool isFriendly){
    projectile *createdProjectile = malloc(sizeof(projectile));
    
    static int id = 0;
    createdProjectile->id = id;
    id++;

    char path[50];
    sprintf(path, "./assets/projectiles/%s", projectileFileName);
    FILE *projectile_file = fopen(path,"r");
    char line_cache[255];
    char stat_name[255];
    char stat_value[255];
    createdProjectile->isFriendly = false;
    this->projectileRenderer.animationId = NULL;
    while(fgets(line_cache, 255, projectile_file) != NULL){
        sscanf(line_cache,"%[^ ] = %[^\n]", stat_name, stat_value);
        switch(getProjectileConfigFileParamFromString(stat_name)){
            case P_TEX_REF:
                createdProjectile->projectileRenderer.texref = malloc(sizeof(char)*(strlen(stat_value)+1));
                strcpy(createdProjectile->texref, stat_value);
                break;
            case P_TEX_ANIM_FRAMES :
                createdProjectile->projectileRenderer.nOfFrames = atoi(stat_value);
                break;
            case P_WEAPON_PERFORANCE :
                createdProjectile->perforance = atoi(stat_value);
                break;
            case P_WEAPON_DAMAGE :
                createdProjectile->damage = atof(stat_value);
                break;
            case P_WEAPON_SPEED :
                createdProjectile->speed = atof(stat_value);
                break;
            case P_WEAPON_TYPE :
                createdProjectile->type = getWeaponTypeFromString(stat_value);
                break;
            case P_WIDTH :
                createdProjectile->projectileRenderer.width = atoi(stat_value);
                break;
            case P_HEIGHT:
                createdProjectile->projectileRenderer.height = atoi(stat_value);
                break;
            case P_NONE :
                break;
        }
    }
    fclose(projectile_file);
    createdProjectile->projectileRenderer.texref = malloc(sizeof(char)*50);
    sprintf(createdProjectile->projectileRenderer.texref, "p_%s.png", createdProjectile->projectileRenderer.texref);
    createdProjectile->projectileRenderer.texture = GAME.textureManager->getTexture(createdProjectile->projectileRenderer.texref);
    createdProjectile->projectileRenderer.currentFrame = 0;
    
    createdProjectile->isFriendly = isFriendly;
    createdProjectile->x = xpos;
    createdProjectile->y = ypos;
    createdProjectile-rotation = rotation;
    createdProjectile->speedx = createdProjectile->speed * cos(rotation);
    createdProjectile->speedy = createdProjectile->speed * sin(rotation);

    return createdProjectile;
}

void projectileUpdate(void *self){
    projectile *this = self;
    float endPosX = this->speedx+this->x;
    float endPosY = this->speedy+this->y;

    list *GameObjects = this->parent->game->gameObjects;
    for(int index = 0; index < GameObjects->length; index++){
        GameObject *target = getDataAtIndex(*GameObjects, index);
        if(target->type == GOT_Robot){
            robot *actor = target->actor;
            float distStartPointCenter = sqrt(pow(this->x - (actor->x + actor->width/2),2) + pow(this->y - (actor->y + actor->height/2),2));
            float alphaDiv = this->speed * distStartPointCenter;
            float alpha = acos((endPosX*(actor->x + actor->width/2) + endPosY * (actor->y + actor->height/2))/alphaDiv);
            float tang = distStartPointCenter * cos(alpha);
            float tangX = tang * cos(alpha);
            float tangY = tang * sin(alpha);
            float normalPointX = tangX+this->x;
            float normalPointY = tangY+this->y;
            float distNormal = sqrt(pow(normalPointX - (actor->x + actor->width/2),2) + pow(normalPointY - (actor->y + actor->height/2),2));
            float r = min(actor->width, actor->height)/2;
            if(normalPointX >= min(this->x, endPosX) && normalPointX <= max(this->x, endPosX) && normalPointY >= min(this->y, endPosY) && normalPointY <= max(this->y, endPosY)){
                if(distNormal < r && actor->isAlive()){
                    newHit(this->damage, normalPointX, normalPointY, this->type, this->parent, target);
                    this->perforance--;
                    if(this->perforance == 0){
                        this->delete();
                        return;
                    }
                }
            }
        }
    }
    SDL_DisplayMode *DM=malloc(sizeof(SDL_DisplayMode));
    SDL_GetCurrentDisplayMode(0, DM);
    int wWidth = DM->w;
    int wHeight = DM->h;
    if(endPosX < -this->projectileRenderer.width || endPosX > wWidth + this->projectileRenderer.width || endPosY < -this->projectileRenderer.height || endPosY > wHeight + this->projectileRenderer.height){
        this->delete();
        return;
    }
    this->x+=this->speedx;
    this->y+=this->speedy;
}

void projectileRender(void *self){
    projectile *this = self;
    GameObject *parent = this->parent;
    SDL_Rect rect={ROUND(this->x)+(this->width/2),ROUND(this->y),this->projectileRenderer.width, this->projectileRenderer.height};
    SDL_Rect srcrect={this->projectileRenderer.currentFrame*this->projectileRenderer.width, 0, this->projectileRenderer.height, this->projectileRenderer.width};
    SDL_RenderCopyEx(parent->game->renderer, this->projectileRenderer.texture,&srcrect,&rect,-this->rotation*90/(M_PI/2) + 180,NULL,SDL_FLIP_NONE);
}

void projectileDelete(void *self){
    projectile *this = self;
    free(this->projectileRenderer.texref);  
    free(this->projectileRenderer.textureName);
    if(this->projectileRenderer.animationId) free(this->projectileRenderer.animationId);
    deleteInList(PROJECTILE_MANAGER->projectiles, this);
    free(this);
}

void createProjectile(Game *GAME, char *projectileFileName, float xpos, float ypos, float rotation, GameObject *parent){
    projectile *createdProjectile = newProjectile(GAME, projectileFileName, xpos, ypos, rotation, true);
    createdProjectile->parent = parent;
    createdProjectile->update = projectileUpdate;
    createdProjectile->render = projectileRender;
    createdProjectile->delete = projectileDelete;
    pushInList(PROJECTILE_MANAGER->projectiles, createProjectile);
}


void clearAndFree(){
    forEach(PROJECTILE_MANAGER->projectiles, projectileDelete);
    forEach(PROJECTILE_MANAGER->hits, hitDelete);
    free(PROJECTILE_MANAGER->projectiles);
    free(PROJECTILE_MANAGER->hits);
    free(PROJECTILE_MANAGER);
}

projectileManager *initProjectileManager(){
    projectileManager *projectileManager = malloc(sizeof(projectileManager));
    projectileManager->empty = clearAndFree;
    projectileManager->newProjectile = createProjectile;
    projectileManager->newHit = newHit;
    projectileManager->projectiles = newList(COMPARE_PTR);
    projectileManager->hits = newList(COMPARE_PTR);
    return projectileManager;
}

#endif