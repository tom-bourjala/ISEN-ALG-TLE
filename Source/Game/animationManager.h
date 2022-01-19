#include <stdio.h>
#include <stdlib.h>
#include "../List/SmartList.h"

#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

typedef struct animation animation;

typedef struct
{
    void (*addAnim)(char* id, int* toIncrement, int nOfFrames, int delay);
    void (*killAnim)(char* id);
    animation *(*getAnim)(char* id);
    list *animList;
} animationManager;

struct animation
{
    void (*update)(void *self);
    char* id;
    int* toIncrement;
    int nOfFrames;
    int delay;
    int timer;
    animationManager *manager;
};

animationManager *initAnimManager();

#endif