#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "../Robots/robots.h"
#include "projectileManager.h"
#include "../Game/game.h"
#define max(a,b) (a>=b?a:b)
#define min(a,b) (a<=b?a:b)

typedef enum{P_TEX_REF, P_TEX_ANIM_FRAMES,P_WIDTH, P_HEIGHT, P_WEAPON_DAMAGE, P_WEAPON_SPEED, P_WEAPON_PERFORANCE, P_WEAPON_TYPE, P_NONE} projectileConfigFileParam;

projectileConfigParam getProjectileConfigFileParamFromString(char *fileParamString){
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

projectile *newProjectile(Game GAME,char *projectileFileName, int xpos, int ypos, float rotation, bool isFriendly){
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
    while(fgets(line_cache, 255, projectile_file) != NULL){
        sscanf(line_cache,"%[^ ] = %[^\n]", stat_name, stat_value);
        switch(getRobotConfigFileParamFromString(stat_name)){
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
    sprintf(createdProjectile->projectileRenderer.animationId, "p_%s.png", createdProjectile->projectileRenderer.texref);
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
                if(distNormal < r){
                    //Gérer/Génére le hit
                    this->perforance--;
                    if(this->perforance == 0){
                        //DELETE BULLET
                        //RETURN
                    }
                }
            }
        }
    }
    SDL_DisplayMode *DM=malloc(sizeof(SDL_DisplayMode));
    SDL_GetCurrentDisplayMode(0, DM);
    int wWidth = DM->w;
    int wHeight = DM->h;
    if(endPosX < 0 || endPosX > wWidth || endPosY < 0 || endPosY > wWidth){
        //KILL
        //RETURN
    }
    this->x+=this->speedx;
    this->y+=this->speedy;
}

void robotRender(void *self){
    GameObject *thisGameObject = self;
    projectile *this = thisGameObject->actor;
    SDL_Rect rect={this->x,this->y,this->width,this->height};

    SDL_Rect srcrect={this->walk.currentFrame*64,0,64,64};
    SDL_RenderCopyEx(thisGameObject->game->renderer, this->walk.texture,&srcrect,&rect,-this->rotation*90/(M_PI/2) + 180,NULL,SDL_FLIP_NONE);
}

void robotDelete(void *self){
    GameObject *thisGameObject = self;
    projectile *this = thisGameObject->actor;
    free(this->name);
    free(this->texref);  
    free(this->walk.textureName); 
    free(this);
}

GameObject *newGameObject_Robot(Game *GAME, char *projectileFileName, int xpos, int ypos){
    GameObject *gameObject = malloc(sizeof(GameObject));
    gameObject->actor = newRobot(*GAME, projectileFileName, xpos, ypos);
    gameObject->type = GOT_Robot;
    gameObject->game = GAME;
    gameObject->update = projectileUpdate;
    gameObject->render = robotRender;
    gameObject->delete = robotDelete;
    gameObject->isAlive = robotIsAlive;
    return gameObject;
}

TEX_REF
WEAPON_DAMAGE
WEAPON_SPEED
WEAPON_DELAY
WEAPON_RANGE
WEAPON_PERFORANCE
WEAPON_TYPE