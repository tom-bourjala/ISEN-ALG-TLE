#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include "../Game/game.h"
#include "../Game/projectileManager.h"
#include "../List/SmartList.h"
#include "../Robots/robots.h"
#include "robotAi.h"

typedef struct{
    float vx;
    float vy;
} vectAi;

typedef struct{
    float v;
    float teta;
} vectRot;

float distBetweenTwoPoints(float x1, float y1, float x2, float y2){
    return sqrt(pow((x1 + actor->width/2.0) - (turret->x + turret->width/2.0),2) + pow((actor->y + actor->height/2.0) - (turret->y + turret->height/2.0),2));
}

float modulo2Pi(float angle){
    while(angle < M_PI) angle += M_PI*2;
    while(angle > M_PI) angle -= M_PI*2;
    return angle;
}

vectAi vectRotToVectAi(vectRot rot){
    vectAi ai;
    ai.vx = rot.v*cos(rot.teta);
    ai.vy = rot.v*sin(rot.teta);
    return ai;
}

vectRot vectAiToVectRot(vectAi ai){
    vectRot rot;
    rot.teta = atan2f(ai.vx, ai.vy);
    rot.v = sqrt(pow(ai.vx,2) + pow(ai.vy, 2));
    return rot;
}

vectAi crunchVectAi(vectAi vect, float max){
    vectRot vectRot = vectAiToVectRot(vect);
    if(vectRot.v > max) vectRot.v = max;
    return vectRotToVectAi(vectRot);
}

void freeVectRot(void *self){vectRot *vect = self; free(vect);}

vectAi getVectAllyProximity(GameObject *robotObj){
    list *gameObjects = robotObj->game->gameObjects;
    list *escapeVectors = newList(COMPARE_PTR);
    for(int index = 0; index < gameObjects->length; index++){
        GameObject *targetObj = getDataAtIndex(*gameObjects, index);
        if(targetObj->type == GOT_Robot){
            if(targetObj->isAlive(targetObj)){
                robot *targetRobot = targetObj->actor;
                robot *currentRobot = robotObj->actor;
                float distBetweenAlly = distBetweenTwoPoints(currentRobot->x, currentRobot->y, targetRobot->x, targetRobot->y);
                if(distBetweenAlly < 2*currentRobot->radius){
                    vectRot *ev = malloc(sizeof(vectRot));
                    ev->v = pow((1.0/distBetweenAlly),5);
                    ev->teta = modulo2Pi(atan2f(targetRobot->x - currentRobot->x, targetRobot->y - currentRobot->y) + M_PI);
                    appendInList(escapeVectors, ev);
                }
            }
        }
    }
    vectAi result = {0.0,0.0};
    for(int index = 0; index < escapeVectors->length; index++){
        vectRot *vectRot = getDataAtIndex(*escapeVectors, index);
        vectAi vectAi = vectRotToVectAi(*vectRot);
        result.vx += vectAi.x;
        result.vy += vectAi.y; 
    }
    if(escapeVectors->length){
        result.vx /= escapeVectors->length;
        result.vy /= escapeVectors->length;
    }
    forEach(escapeVectors, freeVectRot);
    emptyList(escapeVectors);
    free(escapeVectors);
    return result;
}

vectAi getVectBorderProximity(GameObject *robotObj){
    robot *currentRobot = robotObj->actor;
    map_dataGrid dataGrid = robotObj->game->mapManager->currentMap->dataGrid;
    list *escapeVectors = newList(COMPARE_PTR);
    int samplingRate = 6;
    int currentX = round(currentRobot->x);
    int currentY = round(currentRobot->y);
    for(int x = currentX - (currentRobot->radius * 2); x < currentX + (currentRobot->radius * 2); x++){
        for(int y = currentY - (currentRobot->radius * 2); y < currentY + (currentRobot->radius * 2); y++){
            if(x >= 0 && x < dataGrid.w && y >= 0 && y < dataGrid.h){
                if(!((x*x + y*y) % samplingRate)){
                    map_cell *cell = getCellFromDataGrid(dataGrid, x, y);
                    if(cell->type != MCT_PATH && cell->type != MCT_PATH_NS){
                        float distInBetween = distBetweenTwoPoints(currentRobot->x, currentRobot->y, x, y);
                        vectRot *ev = malloc(sizeof(vectRot));
                        ev->v = pow((1.0/distInBetween),5);
                        ev->teta = modulo2Pi(atan2f(x - currentRobot->x, y - currentRobot->y) + M_PI);
                        appendInList(escapeVectors, ev);
                    }
                }
            }
        }
    }
    vectAi result = {0.0,0.0};
    for(int index = 0; index < escapeVectors->length; index++){
        vectRot *vectRot = getDataAtIndex(*escapeVectors, index);
        vectAi vectAi = vectRotToVectAi(*vectRot);
        result.vx += vectAi.x;
        result.vy += vectAi.y; 
    }
    if(escapeVectors->length){
        result.vx /= escapeVectors->length;
        result.vy /= escapeVectors->length;
    }
    forEach(escapeVectors, freeVectRot);
    emptyList(escapeVectors);
    free(escapeVectors);
    return result;
}

vectAi getVectTargetNode(GameObject *robotObj){
    robot *currentRobot = robotObj->actor;
    vectAi result = vectRotToVectAi((vectRot){currentRobot->maxSpeed, atan2f(currentRobot->x - currentRobot->targetNode->x, currentRobot->y - currentRobot->targetNode->y)});
    return result;
}

void updateRobotPathAi(GameObject *robotObj){
    robot *robot = robotObj->actor;
    vectAi allyProximity = getVectAllyProximity(robotObj);
    vectAi borderProximity = getVectBorderProximity(robotObj);
    vectAi targetNode = getVectTargetNode(robotObj);
    vectAi newSpeedVect;
    newSpeedVect.vx = allyProximity.x + borderProximity.x + targetNode.x + robot->speedx;
    newSpeedVect.vy = allyProximity.y + borderProximity.y + targetNode.y + robot->speedy;
    newSpeedVect = crunchVectAi(newSpeedVect);
    robot->speedx = newSpeedVect.vx;
    robot->speedy = newSpeedVect.vy;
    if(distBetweenTwoPoints(robot->x + robot->speedx, robot->y + robot->speedy, robot->targetNode->x, robot->targetNode->y) >= robot->radius*3){
        if(robot->targetNode->next){
            if(robot->targetNode->nextAlt){
                if(robot->seed % 2) robot->targetNode = robot->targetNode->nextAlt;
                else robot->targetNode = robot->targetNode->next;
                robot->seed /= 2;
            }else robot->targetNode = robot->targetNode->next;
        }
    }
}