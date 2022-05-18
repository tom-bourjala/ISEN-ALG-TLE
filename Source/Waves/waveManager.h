#pragma once
#include "../List/SmartList.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Maps/mapManager.h"

typedef struct wave
{
    list *chunks;
    time_t clock;
    void *parent;
} wave;

typedef struct waveManager
{
    wave *currentWave;
    void (*nextWave)(void);
    void (*pause)(void);
    void (*resume)(void);
    bool isWaveActive;
    void *parent;
    int waveNumber;
    float difficulty;
} waveManager;


typedef struct waveSpawner
{
    int number;
    int id;
    int seed;
    map_node *spawnLocation;
}waveSpawner;


typedef struct waveChunk
{
    list *waveSpawner;
    time_t timer;
    int treshold;
} waveChunk;

