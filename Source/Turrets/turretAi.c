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
    if(distanceIB <= turret->range)
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
    if(!turretObject->game->animationManager->getAnim(this->canon.animationId)){
        turretObject->game->animationManager->addAnim(this->canon.animationId, &this->canon.currentFrame, this->canon.nOfFrames, 1);
        turretObject->game->projectileManager->newProjectile(turretObject->game, this->projectileName, this->x + (this->width/2), this->y + (this->height/2), this->rotation, turretObject);
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
        // printf("CurrentRotation = %f, TargetIdealAngle = %f, delta = %f\n", currentTurretRotation, TargetFireAngle, delta);
        // printf("Rh = %d, Rw = %d, Th = %d, Tw = %d\n", robot->height,robot->width,turret->height,turret->width);
        if(fabs(delta) < turret->maxRotationSpeed){
            turret->rotation = TargetFireAngle;
            tryShoot(turretObject);
        } else {
            if(fabs(delta) < M_PI/2.0)
                turret->rotation += turret->maxRotationSpeed * (delta >= 0 ? -1.0 : 1.0);
            else
                turret->rotation += turret->maxRotationSpeed * (isEnemyBypassingClockwise(*turretObject, *closestTarget) ? 1.0 : -1.0);
        }
        if(turret->rotation > M_PI) turret->rotation -= 2.0*M_PI;
        if(turret->rotation < -M_PI) turret->rotation += 2.0*M_PI;
    }
}