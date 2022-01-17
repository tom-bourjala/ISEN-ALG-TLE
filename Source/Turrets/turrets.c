#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "turrets.h"
#include "../Game/game.h"

typedef enum{TP_NAME, TP_TEX_REF, TP_TEX_ANIM_FRAMES, TP_ROTATION_SPEED, TP_ROTATION_ACCELERATION, TP_WEAPON_DAMAGE, TP_WEAPON_SPEED, TP_WEAPON_DELAY, TP_WEAPON_TYPE,TP_NONE} turretConfigFileParam;

turretConfigFileParam getTurretConfigFileParamFromString(char *fileParamString){
    if(!strcmp("NAME", fileParamString)) return TP_NAME;
    if(!strcmp("TEX_REF", fileParamString)) return TP_TEX_REF;
    if(!strcmp("TEX_ANIM_FRAMES", fileParamString)) return TP_TEX_ANIM_FRAMES;
    if(!strcmp("ROTATION_SPEED", fileParamString)) return TP_ROTATION_SPEED;
    if(!strcmp("ROTATION_ACCELERATION", fileParamString)) return TP_ROTATION_ACCELERATION;
    if(!strcmp("WEAPON_DAMAGE", fileParamString)) return TP_WEAPON_DAMAGE;
    if(!strcmp("WEAPON_SPEED", fileParamString)) return TP_WEAPON_SPEED;
    if(!strcmp("WEAPON_DELAY", fileParamString)) return TP_WEAPON_DELAY;
    if(!strcmp("WEAPON_TYPE", fileParamString)) return TP_WEAPON_TYPE;
    return TP_NONE;
}

weaponType getWeaponTypeFromString(char *fileParamString){
    if(!strcmp("BALLISTIC", fileParamString)) return BALLISTIC;
    if(!strcmp("PLASMA", fileParamString)) return PLASMA;
    if(!strcmp("EXPLOSIVE", fileParamString)) return EXPLOSIVE;
    return 0;
}

turret *newTurret(Game GAME,char *turretFileName, int xpos, int ypos){
    turret *createdTurret = malloc(sizeof(turret));
    char path[50];
    sprintf(path, "./assets/turrets/%s", turretFileName);
    FILE *turret_file = fopen(path,"r");
    char stat_name[255];
    char stat_value[255];
    while(fscanf(turret_file,"%[^ ]= %s",stat_name,stat_value) != EOF){
        printf("PARAM \"%s\" = \"%s\"\n", stat_name, stat_value);
        switch(getTurretConfigFileParamFromString(stat_name)){
            case TP_NAME:
                createdTurret->name = malloc(sizeof(char)*(strlen(stat_value)-1));
                strcpy(createdTurret->name, stat_value);
                break;
            case TP_TEX_REF:
                createdTurret->texref = malloc(sizeof(char)*(strlen(stat_value)-1));
                strcpy(createdTurret->texref, stat_value);
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
            case TP_WEAPON_DAMAGE :
                createdTurret->weapon.projectileDamage = atof(stat_value);
                break;
            case TP_WEAPON_SPEED :
                createdTurret->weapon.projectileSpeed = atof(stat_value);
                break;
            case TP_WEAPON_DELAY :
                createdTurret->weapon.delay = atof(stat_value);
                break;
            case TP_WEAPON_TYPE :
                createdTurret->weapon.type = getWeaponTypeFromString(stat_value);
                break;
            case TP_NONE :
                break;
        }
    }
    
    createdTurret->base.textureName = malloc(sizeof(char)*50);
    sprintf(createdTurret->base.textureName, "tur_%s_base", createdTurret->texref);
    createdTurret->base.texture = GAME.textureManager->getTexture(createdTurret->base.textureName, 0);

    createdTurret->support.textureName = malloc(sizeof(char)*50);
    sprintf(createdTurret->support.textureName, "tur_%s_sup", createdTurret->texref);
    createdTurret->canon.texture = GAME.textureManager->getTexture(createdTurret->canon.textureName, 0);

    createdTurret->canon.textureName = malloc(sizeof(char)*50);
    sprintf(createdTurret->canon.textureName, "tur_%s_can_anim", createdTurret->texref);
    createdTurret->support.texture = GAME.textureManager->getTexture(createdTurret->support.textureName, 0);

    createdTurret->x = xpos;
    createdTurret->y = ypos;
    createdTurret->rotation = 0.0;
    return createdTurret;
}

void turretUpdate(void *self){
    GameObject *thisGameObject = self;
    turret *this = thisGameObject->actor;
    this->rotation += 0.01;
}

void turretRender(void *self){
    GameObject *thisGameObject = self;
    turret *this = thisGameObject->actor;
    SDL_Rect rect={this->x,this->y-64,this->x+64,this->y};
    SDL_RenderCopyEx(thisGameObject->game.renderer, this->base.texture,NULL,&rect,0,NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(thisGameObject->game.renderer, this->support.texture,NULL,&rect,-this->rotation*90/(M_PI/2),NULL,SDL_FLIP_NONE);
    SDL_RenderCopyEx(thisGameObject->game.renderer, this->canon.texture,NULL,&rect,-this->rotation*90/(M_PI/2),NULL,SDL_FLIP_NONE);
}

void turretDelete(void *self){
    GameObject *thisGameObject = self;
    turret *this = thisGameObject->actor;
    free(this->name);
    free(this->texref);  
    free(this->base.textureName); 
    free(this->support.textureName);
    free(this->canon.textureName); 
    free(this);
}

bool turretIsAlive(void *self){
    GameObject *thisGameObject = self;
    turret *this = thisGameObject->actor;
    return true;
}

GameObject *newGameObject_Turret(Game GAME, char *turretFileName, int xpos, int ypos){
    GameObject *GameObject = malloc(sizeof(GameObject));
    GameObject->actor = newTurret(GAME, turretFileName, xpos, ypos);
    GameObject->game = GAME;
    GameObject->update = turretUpdate;
    GameObject->render = turretRender;
    GameObject->delete = turretDelete;
    GameObject->isAlive = turretIsAlive;
    return GameObject;
}
