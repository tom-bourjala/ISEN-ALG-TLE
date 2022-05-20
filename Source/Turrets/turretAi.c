#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include "../Game/game.h"
#include "../Game/projectileManager.h"
#include "../List/SmartList.h"
#include "../Robots/robots.h"
#include "../Turrets/turrets.h"
#include "turretAi.h"

GameObject *getClosestEnemy(GameObject turretObject){
    list *GameObjects = turretObject.game->gameObjects;
    turret *turret = turretObject.actor;
    GameObject *closestTarget = NULL;
    float minDist = FLT_MAX;
    for(int index = 0; index < GameObjects->length; index++){
        GameObject *target = getDataAtIndex(*GameObjects, index);
        if(target->type == GOT_Robot){
            robot *actor = target->actor;
            float distanceIB = sqrt(pow(actor->x - (turret->x + turret->width/2),2) + pow(actor->y - (turret->y + turret->height/2),2));
            if(distanceIB <= minDist){
                minDist = distanceIB;
                closestTarget = target;
            }
        }
    }
    return closestTarget;
}

GameObject *getClosestEnemyInRange(GameObject turretObject){
    GameObject *closestTarget = getClosestEnemy(turretObject);
    if(!closestTarget) return NULL;
    turret *turret = turretObject.actor;
    robot *actor = closestTarget->actor;
    float distanceIB = sqrt(pow(actor->x - (turret->x + turret->width/2),2) + pow(actor->y - (turret->y + turret->height/2),2));
    // printf("IB=%f, R=%d\n", distanceIB, turret->range);
    if(distanceIB <= turret->currentState->range)
        return closestTarget;
    else
        return NULL;
}

bool isEnemyBypassingClockwise(GameObject turretObject, GameObject target){
    turret *turret = turretObject.actor;
    robot *robot = target.actor;
    float turretAngleFromTarget = atan2(robot->x - (turret->x + turret->width/2), robot->y - (turret->y + turret->height/2));
    float targetMovingAngle = atan2(robot->speedx, robot->speedy);
    float turretAbsoluteMovingAngle = targetMovingAngle - turretAngleFromTarget;
    if(turretAbsoluteMovingAngle > M_PI) turretAbsoluteMovingAngle -= 2.0*M_PI;
    if(turretAbsoluteMovingAngle < -M_PI) turretAbsoluteMovingAngle += 2.0*M_PI;
    return turretAbsoluteMovingAngle <= 0;
}

float getDeltaBetweenTwoAngles(float a1, float a2){
    float delta = a1 - a2;
    if(delta > M_PI) delta -= 2.0*M_PI;
    if(delta < -M_PI) delta += 2.0*M_PI;
    return delta;
}

void tryShoot(GameObject *turretObject){
    turret *this = turretObject->actor;
    if(!turretObject->game->animationManager->getAnim(this->currentState->canon.animationId)){
        turretObject->game->animationManager->addAnim(this->currentState->canon.animationId, &this->currentState->canon.currentFrame, this->currentState->canon.nOfFrames, 1);
    }
}

void updateTurretAi(GameObject *turretObject){
    turret *turret = turretObject->actor;
    GameObject *closestTarget = getClosestEnemyInRange(*turretObject);
    if(closestTarget){
        robot *robot = closestTarget->actor;
        float currentTurretRotation = turret->rotation;
        float TargetFireAngle = atan2(turret->x + (turret->width/2) - robot->x, turret->y + (turret->height/2) - robot->y);
        float delta = getDeltaBetweenTwoAngles(currentTurretRotation, TargetFireAngle);
        if(fabs(delta) < turret->currentState->maxRotationSpeed){
            turret->rotation = TargetFireAngle;
            tryShoot(turretObject);
        } else {
            if(fabs(delta) < M_PI/2.0)
                turret->rotation += turret->currentState->maxRotationSpeed * (delta >= 0 ? -1.0 : 1.0);
            else
                turret->rotation += turret->currentState->maxRotationSpeed * (isEnemyBypassingClockwise(*turretObject, *closestTarget) ? 1.0 : -1.0);
        }
        if(turret->rotation > M_PI) turret->rotation -= 2.0*M_PI;
        if(turret->rotation < -M_PI) turret->rotation += 2.0*M_PI;
    }
    if(turret->currentState->canon.currentFrame == turret->currentState->canon.fireFrame){
        turretObject->game->projectileManager->newProjectile(turretObject->game, turret->currentState->projectileName, turret->x + (turret->width/2), turret->y + (turret->height/2), turret->rotation, turretObject);
    }
}