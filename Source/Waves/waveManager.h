#pragma once
#include "../List/SmartList.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Maps/mapManager.h"

typedef struct
{
    list *chunks;
    int clock;
    void *parent;
} wave;

typedef struct
{
    wave *currentWave;
    void (*update)(void);
    void (*nextWave)(void);
    bool isWaveActive;
    void *parent;
    int waveNumber;
    float difficulty;
} waveManager;


typedef struct
{
    int number;
    int id;
    int seed;
    map_node *spawnLocation;
}waveSpawner;


typedef struct
{
    list *waveSpawner;
    int timer;
    int treshold;
} waveChunk;

