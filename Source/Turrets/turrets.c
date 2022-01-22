#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "turrets.h"
#include "turretAi.h"
#include "../Game/game.h"

typedef enum{TP_NAME, TP_TEX_REF, TP_WIDTH, TP_HEIGHT, TP_TEX_ANIM_FRAMES, TP_ROTATION_SPEED, TP_ROTATION_ACCELERATION, TP_WEAPON_DELAY, TP_WEAPON_RANGE, TP_NONE} turretConfigFileParam;

turretConfigFileParam getTurretConfigFileParamFromString(char *fileParamString){
    if(!strcmp("NAME", fileParamString)) return TP_NAME;
    if(!strcmp("TEX_REF", fileParamString)) return TP_TEX_REF;
    if(!strcmp("WIDTH", fileParamString)) return TP_WIDTH;
    if(!strcmp("HEIGHT", fileParamString)) return TP_HEIGHT;
    if(!strcmp("TEX_ANIM_FRAMES", fileParamString)) return TP_TEX_ANIM_FRAMES;
    if(!strcmp("ROTATION_SPEED", fileParamString)) return TP_ROTATION_SPEED;
    if(!strcmp("ROTATION_ACCELERATION", fileParamString)) return TP_ROTATION_ACCELERATION;
    if(!strcmp("DELAY", fileParamString)) return TP_WEAPON_DELAY;
    if(!strcmp("RANGE", fileParamString)) return TP_WEAPON_RANGE;
    return TP_NONE;
}


turret *newTurret(Game GAME,char *turretFileName, int xpos, int ypos){
    turret *createdTurret = malloc(sizeof(turret));
    
    static int id = 0;
    createdTurret->id = id;
    id++;

    char path[50];
    sprintf(path, "./assets/turrets/%s", turretFileName);
    FILE *turret_file = fopen(path,"r");
    char line_cache[255];
    char stat_name[255];
    char stat_value[255];
    while(fgets(line_cache,255,turret_file) != NULL){
        sscanf(line_cache,"%[^ ] = %[^\n]", stat_name, stat_value);
        switch(getTurretConfigFileParamFromString(stat_name)){
            case TP_NAME:
                createdTurret->name = malloc(sizeof(char)*(strlen(stat_value) + 1));
                strcpy(createdTurret->name, stat_value);
                break;
            case TP_TEX_REF:
                createdTurret->texref = malloc(sizeof(char)*(strlen(stat_value) + 1));
                strcpy(createdTurret->texref, stat_value);
                break;
            case TP_WIDTH :
                createdTurret->width = atoi(stat_value);
                break;
            case TP_HEIGHT :
                createdTurret->height = atoi(stat_value);
                break;
            case TP_TEX_ANIM_FRAMES :
                createdTurret->canon.nOfFrames = atoi(stat_value);
                break;
            case TP_ROTATION_SPEED :
                createdTurret->maxRotationSpeed = atof(stat_value);
                break;
            case TP_ROTATION_ACCELERATION :
                createdTurret->maxRotationAcceleration = atof(stat_value);
                break;
            case TP_WEAPON_DELAY :
                createdTurret->delay = atof(stat_value);
                break;    
            case TP_WEAPON_RANGE:
                createdTurret->range = atof(stat_value);
                break;
            case TP_NONE :
                break;
        }
    }
    fclose(turret_file);
    createdTurret->base.textureName = malloc(sizeof(char)*50);
    sprintf(createdTurret->base.textureName, "tur_%s_base.png", createdTurret->texref);
    createdTurret->base.texture = GAME.textureManager->getTexture(createdTurret->base.textureName);
    
    createdTurret->support.textureName = malloc(sizeof(char)*50);
    sprintf(createdTurret->support.textureName, "tur_%s_sup.png", createdTurret->texref);
    createdTurret->support.texture = GAME.textureManager->getTexture(createdTurret->support.textureName);

    createdTurret->canon.textureName = malloc(sizeof(char)*50);
    sprintf(createdTurret->canon.textureName, "tur_%s_can_anim.png", createdTurret->texref);
    createdTurret->canon.texture = GAME.textureManager->getTexture(createdTurret->canon.textureName);
    createdTurret->canon.currentFrame = 0;

    createdTurret->canon.animationId = malloc(sizeof(char)*50);
    sprintf(createdTurret->canon.animationId, "T%d", createdTurret->id);

    createdTurret->x = xpos;
    createdTurret->y = ypos;
    createdTurret->rotation = 0.0;

    
    return createdTurret;
}

void turretUpdate(void *self){
    GameObject *thisGameObject = self;
    turret *this = thisGameObject->actor;
    // this->rotation = fmod(this->rotation + 0.01,M_PI*2.0);
    updateTurretAi(thisGameObject);
}

void turretRender(void *self){
    GameObject *thisGameObject = self;
    turret *this = thisGameObject->actor;
    SDL_Rect rect={this->x,this->y,this->width,this->height};
    
    SDL_RenderCopyEx(thisGameObject->game->renderer, this->base.texture,NULL,&rect,0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(thisGameObject->game->renderer, this->support.texture,NULL,&rect,-this->rotation*90/(M_PI/2),NULL,SDL_FLIP_NONE);

    SDL_Rect srcrect={this->canon.currentFrame*64,0,64,64};
    SDL_RenderCopyEx(thisGameObject->game->renderer, this->canon.texture,&srcrect,&rect,-this->rotation*90/(M_PI/2),NULL,SDL_FLIP_NONE);
}

void turretDelete(void *self){
    GameObject *thisGameObject = self;
    turret *this = thisGameObject->actor;
    free(this->name);
    free(this->texref);  
    free(this->base.textureName); 
    free(this->support.textureName);
    free(this->canon.textureName);
    free(this->canon.animationId);
    free(this);
}

bool turretIsAlive(void *self){
    GameObject *thisGameObject = self;
    turret *this = thisGameObject->actor;
    return true;
}

GameObject *newGameObject_Turret(Game *GAME, char *turretFileName, int xpos, int ypos){
    GameObject *gameObject = malloc(sizeof(GameObject));
    gameObject->actor = newTurret(*GAME, turretFileName, xpos, ypos);
    gameObject->type = GOT_Turret;
    gameObject->game = GAME;
    gameObject->update = turretUpdate;
    gameObject->render = turretRender;
    gameObject->delete = turretDelete;
    gameObject->isAlive = turretIsAlive;
    return gameObject;
}