#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "robots.h"
#include "../Game/game.h"

typedef enum{ROB_NAME, ROB_TEX_REF, ROB_TEX_ANIM_FRAMES, ROB_LIFE, ROB_WEAPON_DAMAGE, ROB_WEAPON_SPEED, ROB_WEAPON_DELAY, ROB_WEAPON_TYPE, ROB_WEAPON_RANGE, ROB_IS_FRIENDLY, ROB_NONE} robotConfigFileParam;


robotConfigFileParam getRobotConfigFileParamFromString(char *fileParamString){
    if(!strcmp("NAME", fileParamString)) return ROB_NAME;
    if(!strcmp("TEX_REF", fileParamString)) return ROB_TEX_REF;
    if(!strcmp("TEX_ANIM_FRAMES", fileParamString)) return ROB_TEX_ANIM_FRAMES;
    if(!strcmp("WEAPON_DAMAGE", fileParamString)) return ROB_WEAPON_DAMAGE;
    if(!strcmp("WEAPON_SPEED", fileParamString)) return ROB_WEAPON_SPEED;
    if(!strcmp("WEAPON_DELAY", fileParamString)) return ROB_WEAPON_DELAY;
    if(!strcmp("WEAPON_TYPE", fileParamString)) return ROB_WEAPON_TYPE;
    if(!strcmp("WEAPON_RANGE", fileParamString)) return ROB_WEAPON_RANGE;
    if(!strcmp("IS_FRIENDLY", fileParamString)) return ROB_IS_FRIENDLY;
    if(!strcmp("LIFE", fileParamString)) return ROB_LIFE;
    return ROB_NONE;
}

robot *newRobot(Game GAME,char *robotFileName, int xpos, int ypos){
    robot *createdRobot = malloc(sizeof(robot));
    
    static int id = 0;
    createdRobot->id = id;
    id++;

    char path[50];
    sprintf(path, "./assets/robots/%s", robotFileName);
    FILE *robot_file = fopen(path,"r");
    char line_cache[255];
    char stat_name[255];
    char stat_value[255];
    createdRobot->isFriendly = false;
    while(fgets(line_cache,255,robot_file) != NULL){
        sscanf(line_cache,"%[^ ] = %[^\n]", stat_name, stat_value);
        switch(getRobotConfigFileParamFromString(stat_name)){
            case ROB_NAME:
                createdRobot->name = malloc(sizeof(char)*(strlen(stat_value)+1));
                strcpy(createdRobot->name, stat_value);
                break;
            case ROB_LIFE:
                createdRobot->life = atoi(stat_value);
                break;
            case ROB_TEX_REF:
                createdRobot->texref = malloc(sizeof(char)*(strlen(stat_value)+1));
                strcpy(createdRobot->texref, stat_value);
                break;
            case ROB_TEX_ANIM_FRAMES :
                createdRobot->walk.nOfFrames = atoi(stat_value);
                break;
            case ROB_WEAPON_DAMAGE :
                createdRobot->weapon.projectileDamage = atof(stat_value);
                break;
            case ROB_WEAPON_SPEED :
                createdRobot->weapon.projectileSpeed = atof(stat_value);
                break;
            case ROB_WEAPON_DELAY :
                createdRobot->weapon.delay = atof(stat_value);
                break;
            case ROB_WEAPON_TYPE :
                createdRobot->weapon.type = getWeaponTypeFromString(stat_value);
                break;
            case ROB_WEAPON_RANGE :
                createdRobot->weapon.range = atoi(stat_value);
                break;
            case ROB_IS_FRIENDLY :
                createdRobot->isFriendly = true;
                break;
            case ROB_NONE :
                break;
        }
    }
    fclose(robot_file);
    createdRobot->walk.textureName = malloc(sizeof(char)*50);
    sprintf(createdRobot->walk.textureName, "rob_%s_%s_walk.png", createdRobot->isFriendly ? "friendly" : "hostile", createdRobot->texref);
    createdRobot->walk.texture = GAME.textureManager->getTexture(createdRobot->walk.textureName);
    createdRobot->walk.currentFrame = 0;

    createdRobot->x = xpos;
    createdRobot->y = ypos;
    createdRobot->speedx = 2;
    createdRobot->speedy = 1;
    createdRobot->rotation = 0.0;

    return createdRobot;
}

void robotUpdate(void *self){
    GameObject *thisGameObject = self;
    robot *this = thisGameObject->actor;
    if(this->y>=1500 || this->y<=0)
        this->speedy = -this->speedy; 
    if(this->x>=1500 || this->x<=0)
        this->speedx = -this->speedx; 

    this->x+=this->speedx;
    this->y+=this->speedy;

    this->rotation = atan2(this->speedx, this->speedy);
    this->walk.currentFrame = (this->walk.currentFrame + 1) % this->walk.nOfFrames;
}

void robotRender(void *self){
    GameObject *thisGameObject = self;
    robot *this = thisGameObject->actor;
    SDL_Rect rect={this->x,this->y,100,100};

    SDL_Rect srcrect={this->walk.currentFrame*64,0,64,64};
    SDL_RenderCopyEx(thisGameObject->game->renderer, this->walk.texture,&srcrect,&rect,-this->rotation*90/(M_PI/2) + 180,NULL,SDL_FLIP_NONE);
}

void robotDelete(void *self){
    GameObject *thisGameObject = self;
    robot *this = thisGameObject->actor;
    free(this->name);
    free(this->texref);  
    free(this->walk.textureName); 
    free(this);
}

bool robotIsAlive(void *self){
    GameObject *thisGameObject = self;
    robot *this = thisGameObject->actor;
    return this->life > 0;
}

GameObject *newGameObject_Robot(Game *GAME, char *robotFileName, int xpos, int ypos){
    GameObject *gameObject = malloc(sizeof(GameObject));
    gameObject->actor = newRobot(*GAME, robotFileName, xpos, ypos);
    gameObject->game = GAME;
    gameObject->update = robotUpdate;
    gameObject->render = robotRender;
    gameObject->delete = robotDelete;
    gameObject->isAlive = robotIsAlive;
    return gameObject;
}