#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "robots.h"
#include "robotAi.h"
#include "../Game/game.h"
#include "../Game/rendererAddons.h"


typedef enum{ROB_NAME, ROB_TEX_REF, ROB_PROJECTILE_NAME, ROB_WIDTH, ROB_HEIGHT, ROB_SPEED, ROB_TEX_ANIM_FRAMES, ROB_LIFE, ROB_WEAPON_DELAY, ROB_WEAPON_RANGE, ROB_IS_FRIENDLY, ROB_NONE} robotConfigFileParam;


robotConfigFileParam getRobotConfigFileParamFromString(char *fileParamString){
    if(!strcmp("NAME", fileParamString)) return ROB_NAME;
    if(!strcmp("TEX_REF", fileParamString)) return ROB_TEX_REF;
    if(!strcmp("WIDTH", fileParamString)) return ROB_WIDTH;
    if(!strcmp("HEIGHT", fileParamString)) return ROB_HEIGHT;
    if(!strcmp("TEX_ANIM_FRAMES", fileParamString)) return ROB_TEX_ANIM_FRAMES;
    if(!strcmp("WEAPON_DELAY", fileParamString)) return ROB_WEAPON_DELAY;
    if(!strcmp("WEAPON_RANGE", fileParamString)) return ROB_WEAPON_RANGE;
    if(!strcmp("IS_FRIENDLY", fileParamString)) return ROB_IS_FRIENDLY;
    if(!strcmp("PROJECTILE", fileParamString)) return ROB_PROJECTILE_NAME;
    if(!strcmp("LIFE", fileParamString)) return ROB_LIFE;
    if(!strcmp("SPEED", fileParamString)) return ROB_SPEED;
    return ROB_NONE;
}

robot *newRobot(Game GAME, char *robotFileName, int x, int y, map_node *spawnNode, int seed){
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
            case ROB_WEAPON_DELAY :
                createdRobot->delay = atoi(stat_value);
                break;
            case ROB_WEAPON_RANGE :
                createdRobot->range = atoi(stat_value);
                break;
            case ROB_IS_FRIENDLY :
                createdRobot->isFriendly = true;
                break;
            case ROB_WIDTH :
                createdRobot->width = atoi(stat_value);
                break;
            case ROB_HEIGHT:
                createdRobot->height = atoi(stat_value);
                break;
            case ROB_PROJECTILE_NAME:
                createdRobot->projectileName = malloc(sizeof(char)*(strlen(stat_value)+1));
                strcpy(createdRobot->projectileName, stat_value);
                break;
            case ROB_SPEED:
                createdRobot->maxSpeed = atof(stat_value);
            case ROB_NONE :
                break;
        }
    }
    fclose(robot_file);
    createdRobot->walk.textureName = malloc(sizeof(char)*50);
    sprintf(createdRobot->walk.textureName, "rob_%s_%s_walk.png", createdRobot->isFriendly ? "friendly" : "hostile", createdRobot->texref);
    createdRobot->walk.texture = GAME.textureManager->getTexture(createdRobot->walk.textureName);
    createdRobot->walk.currentFrame = 0;
    createdRobot->seed = seed;
    createdRobot->x = x;
    createdRobot->y = y;
    createdRobot->targetNode = spawnNode->next->next;
    createdRobot->lastNode = spawnNode->next;
    createdRobot->speedx = 0.0;
    createdRobot->speedy = 0.0;
    createdRobot->rotation = 0.0;
    createdRobot->rotationCache = 0.0;
    createdRobot->radius = (createdRobot->width + createdRobot->height)/8;
    return createdRobot;
}

void robotUpdate(void *self){
    GameObject *thisGameObject = self;
    robot *this = thisGameObject->actor;
    updateRobotPathAi(thisGameObject);
    this->x+=this->speedx;
    this->y+=this->speedy;
    this->rotationCache = this->rotation;
    this->rotation = (atan2f(this->targetNode->x - this->lastNode->x, this->targetNode->y - this->lastNode->y)*0.4) + (this->rotationCache*0.6);
    this->walk.currentFrame = (this->walk.currentFrame + 1) % this->walk.nOfFrames;
}

void robotRender(void *self){
    GameObject *thisGameObject = self;
    robot *this = thisGameObject->actor;
    SDL_Rect rect={this->x - (this->width/2), this->y - (this->height/2),this->width,this->height};
    SDL_Rect srcrect={this->walk.currentFrame*64,0,64,64};
    SDL_RenderCopyEx(thisGameObject->game->renderer, this->walk.texture,&srcrect,&rect,-this->rotation*90/(M_PI/2) + 180,NULL,SDL_FLIP_NONE);
    if(thisGameObject->game->key_debug != DEBUG_NULL)
    {
        SDL_Color rouge = {255,0,0,255};
        SDL_SetRenderDrawColor(thisGameObject->game->renderer,rouge.r,rouge.g,rouge.b,rouge.a);
        DrawCircle(thisGameObject->game->renderer, this->x, this->y, this->radius);
    }
}

void robotDelete(void *self){
    GameObject *thisGameObject = self;
    robot *this = thisGameObject->actor;
    free(this->name);
    free(this->texref);  
    free(this->walk.textureName);
    deleteInList(thisGameObject->game->gameObjects, thisGameObject);
    free(this);
}

bool robotIsAlive(void *self){
    GameObject *thisGameObject = self;
    robot *this = thisGameObject->actor;
    return this->life > 0;
}

float distTwoPoints(int x1, int y1, int x2, int y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool isSpawnAllowed(int x, int y, int r, list *GameObjects){
    for(int index = 0; index < GameObjects->length; index++){
        GameObject *object = getDataAtIndex(*GameObjects, index);
        if(object->type == GOT_Robot){
            robot *targetRobot = object->actor; 
            if(distTwoPoints(x, y, targetRobot->x, targetRobot->y) < targetRobot->radius + r)
                return false;
        }
    }
    return true;
}

GameObject *newGameObject_Robot(Game *GAME, char *robotFileName, map_node *spawnNode, int seed){
    int spawnSamplingRate = 10;
    robot *robot = newRobot(*GAME, robotFileName, 0, 0, spawnNode, seed);
    int Sx1, Sy1, Sx2, Sy2;
    int decreasingMode;
    if(spawnNode->startData->x1 && spawnNode->startData->x2){
        Sx1 = spawnNode->startData->x1 + robot->width;
        Sx2 = spawnNode->startData->x2 - robot->width;
        if(spawnNode->startData->y1 && spawnNode->startData->y2){
            decreasingMode = 1;
            Sy1 = spawnNode->startData->y1 - robot->height;
            Sy2 = spawnNode->startData->y2 - robot->height;
            robot->speedx = 0.0;
            robot->speedy = robot->maxSpeed;
        }else{
            decreasingMode = 2;
            Sy1 = spawnNode->startData->y1 + robot->height;
            Sy2 = spawnNode->startData->y2 + robot->height;
            robot->speedx = 0.0;
            robot->speedy = -robot->maxSpeed;
        }
    }else{
        decreasingMode = 0;
        Sx1 = spawnNode->startData->x1 - robot->width;
        Sx2 = spawnNode->startData->x2 - robot->width;
        Sy1 = spawnNode->startData->y1 + robot->height;
        Sy2 = spawnNode->startData->y2 - robot->height;
        robot->speedx = robot->maxSpeed;
        robot->speedy = 0.0;
    }
    int spawnX = (Sx1 + Sx2)/2; 
    int spawnY = (Sy1 + Sy2)/2;
    int decreaseLevel = 0, decreaseTryNumber = 0;
    while(!isSpawnAllowed(spawnX, spawnY, robot->radius, GAME->gameObjects)){
        if(decreaseTryNumber >= spawnSamplingRate){
            decreaseTryNumber = 0;
            decreaseLevel += robot->radius / 2;
        }
        srand(time(NULL)+rand());
        if(decreasingMode){
            spawnX = Sx1 + (rand()%(Sx2-Sx1));
            if(decreasingMode == 1) spawnY = Sy1 + decreaseLevel;
            else spawnY = Sy1 - decreaseLevel;
        }else {
            spawnX = Sx1 - decreaseLevel;
            spawnY = Sy1 + (rand()%(Sy2-Sy1));
        }
        decreaseTryNumber++;
        // printf("TRY %d,%d\n", spawnX, spawnY);
    }
    // printf("1(%d,%d) 2(%d,%d) S(%d,%d)\n", Sx1, Sy1, Sx2, Sy2, spawnX, spawnY);
    robot->x = spawnX;
    robot->y = spawnY;
    GameObject *gameObject = malloc(sizeof(GameObject));
    gameObject->actor = robot;
    gameObject->type = GOT_Robot;
    gameObject->game = GAME;
    gameObject->update = robotUpdate;
    gameObject->render = robotRender;
    gameObject->delete = robotDelete;
    gameObject->isAlive = robotIsAlive;
    return gameObject;
}