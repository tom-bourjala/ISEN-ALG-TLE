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
#include "rendererAddons.h"

#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)
#define ABS(X)  ((X>=0)? X : -(X) ) 
#define ROUND(X)  (X>=0)? (int) (X + 0.5) : (int)-(ABS(X) +0.5)

typedef enum{P_TEX_REF, P_TEX_ANIM_FRAMES,P_WIDTH, P_HEIGHT, P_WEAPON_DAMAGE, P_WEAPON_SPEED, P_WEAPON_PERFORANCE, P_WEAPON_TYPE, P_NONE} projectileConfigFileParam;

projectileManager *PROJECTILE_MANAGER = NULL;


void hitDelete(void *self){
    hit *this = self;
    deleteInList(PROJECTILE_MANAGER->hits, this);
    free(this);
}

void newHit(int damage, float x, float y, weaponType type, void *parent, void *target){
    hit *createdHit = malloc(sizeof(hit));
    createdHit->delete = hitDelete;
    createdHit->parent = parent;
    createdHit->target = target;
    createdHit->damage = damage;
    createdHit->x = x;
    createdHit->y = y;
    createdHit->parent = parent;
    pushInList(PROJECTILE_MANAGER->hits, createdHit);
}

void applyHit(void *self){
    hit *this = self;
    GameObject *targetObject = this->target;
    robot *target = targetObject->actor;
    target->life -= this->damage;
    if(targetObject->game->key_debug == DEBUG_HITBOX)
        appendInList(targetObject->game->gameObjects, newGameObject_Debug(targetObject->game, this->x, this->y, 600, DO_Hit));
    if(!targetObject->isAlive(targetObject)){
        targetObject->delete(targetObject);
    }
    this->delete(this);
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

projectile *newProjectile(void *game,char *projectileFileName, float xpos, float ypos, float rotation, bool isFriendly){
    projectile *createdProjectile = malloc(sizeof(projectile));
    Game *GAME = game;
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
    createdProjectile->projectileRenderer.animationId = NULL;
    while(fgets(line_cache, 255, projectile_file) != NULL){
        sscanf(line_cache,"%[^ ] = %[^\n]", stat_name, stat_value);
        switch(getProjectileConfigFileParamFromString(stat_name)){
            case P_TEX_REF:
                createdProjectile->projectileRenderer.texref = malloc(sizeof(char)*(strlen(stat_value)+1));
                strcpy(createdProjectile->projectileRenderer.texref, stat_value);
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
    char *textureName = malloc(sizeof(char)*50);
    sprintf(textureName, "p_%s.png", createdProjectile->projectileRenderer.texref);
    createdProjectile->projectileRenderer.texture = GAME->textureManager->getTexture(textureName);
    createdProjectile->projectileRenderer.currentFrame = 0;
    
    createdProjectile->isFriendly = isFriendly;
    createdProjectile->x = xpos;
    createdProjectile->y = ypos;
    createdProjectile->rotation = rotation;
    createdProjectile->speedx = -createdProjectile->speed * sin(rotation);
    createdProjectile->speedy = -createdProjectile->speed * cos(rotation);

    return createdProjectile;
}

void projectileUpdate(void *self){
    projectile *this = self;
    GameObject *parent = this->parent;
    float endPosX = this->speedx+this->x;
    float endPosY = this->speedy+this->y;
    list *GameObjects = parent->game->gameObjects;
    for(int index = 0; index < GameObjects->length; index++){
        GameObject *target = getDataAtIndex(*GameObjects, index);
        if(target->type == GOT_Robot && target->isAlive(target)){
            robot *actor = target->actor;
            float targetX = actor->x + actor->width/2;
            float targetY = actor->y + actor->height/2;
            float distEndPointCenter = sqrt(pow(endPosX - targetX,2) + pow(endPosY- targetY,2));
            float r = actor->radius;
            if(distEndPointCenter < r){
                newHit(this->damage, endPosX, endPosY, this->type, this->parent, target);
                this->perforance--;
                if(this->perforance == 0){
                    this->delete(this);
                    return;
                }
            }
        }
    }
    SDL_DisplayMode *DM=malloc(sizeof(SDL_DisplayMode));
    SDL_GetCurrentDisplayMode(0, DM);
    int wWidth = DM->w;
    int wHeight = DM->h;
    if(endPosX < -this->projectileRenderer.width || endPosX > wWidth + this->projectileRenderer.width || endPosY < -this->projectileRenderer.height || endPosY > wHeight + this->projectileRenderer.height){
        this->delete(this);
        return;
    }
    this->x+=this->speedx;
    this->y+=this->speedy;
}

void projectileRender(void *self){
    projectile *this = self;
    GameObject *parent = this->parent;
    SDL_Rect rect={ROUND(this->x)+(this->projectileRenderer.width/2),ROUND(this->y),this->projectileRenderer.width, this->projectileRenderer.height};
    SDL_Rect srcrect={this->projectileRenderer.currentFrame*this->projectileRenderer.width, 0, this->projectileRenderer.width, this->projectileRenderer.height};
    SDL_RenderCopyEx(parent->game->renderer, this->projectileRenderer.texture,&srcrect,&rect,-this->rotation*90/(M_PI/2) + 180,NULL,SDL_FLIP_NONE);
}

void projectileDelete(void *self){
    projectile *this = self;
    free(this->projectileRenderer.texref);
    if(this->projectileRenderer.animationId) free(this->projectileRenderer.animationId);
    deleteInList(PROJECTILE_MANAGER->projectiles, this);
    free(this);
}

void createProjectile(void *GAME, char *projectileFileName, float xpos, float ypos, float rotation, void *parent){
    projectile *createdProjectile = newProjectile(GAME, projectileFileName, xpos, ypos, rotation, true);
    createdProjectile->parent = parent;
    createdProjectile->update = projectileUpdate;
    createdProjectile->render = projectileRender;
    createdProjectile->delete = projectileDelete;
    pushInList(PROJECTILE_MANAGER->projectiles, createdProjectile);
}


void clearAndFree(){
    if(PROJECTILE_MANAGER->projectiles->length) forEach(PROJECTILE_MANAGER->projectiles, projectileDelete);
    if(PROJECTILE_MANAGER->hits->length) forEach(PROJECTILE_MANAGER->hits, hitDelete);
    free(PROJECTILE_MANAGER->projectiles);
    free(PROJECTILE_MANAGER->hits);
    free(PROJECTILE_MANAGER);
}

void updateProjectiles(){
    forEach(PROJECTILE_MANAGER->projectiles, projectileUpdate);
}

void renderProjectiles(){
    forEach(PROJECTILE_MANAGER->projectiles, projectileRender);
}

void applyHits(){
    forEach(PROJECTILE_MANAGER->hits, applyHit);
}

projectileManager *initProjectileManager(){
    projectileManager *manager = malloc(sizeof(projectileManager));
    manager->empty = clearAndFree;
    manager->newProjectile = createProjectile;
    manager->newHit = newHit;
    manager->projectiles = newList(COMPARE_PTR);
    manager->hits = newList(COMPARE_PTR);
    manager->updateProjectiles = updateProjectiles;
    manager->renderProjectiles = renderProjectiles;
    manager->applyHits = applyHits;
    PROJECTILE_MANAGER = manager;
    return manager;
}