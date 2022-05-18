#include "./waveGenerator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Game/game.h"
#include "../Maps/mapManager.h"

waveSpawner *newSpawner(int number,int id,int seed, map_node *spawnLocation){
    waveSpawner *newSpawner = malloc(sizeof(waveSpawner));
    newSpawner->number = number;
    newSpawner->id = id;
    newSpawner->seed = seed;
    newSpawner->spawnLocation = spawnLocation;
    return newSpawner;
}

waveChunk *newChunk(){
    waveChunk *newChunk = malloc(sizeof(waveChunk));
    newChunk->timer = -1;
    newChunk->treshold = -1;
    return newChunk;
}

wave *newWave(waveManager *parent){
    wave *newWave = malloc(sizeof(wave));
    newWave->chunks = NULL;
    newWave->clock = -1;
    newWave->parent = parent;
    return newWave;
}

void archetype_smallTeam(list *chunks,float weight){

}

wave *generateNewWave(int waveNumber,float difficulty,waveManager *parent){
    srand(waveNumber);
    float weight = waveNumber*difficulty;
    switch (waveNumber)
    {
    case 1:
        
        break;
    case 6:
        
        break;
    case 11:
        
        break;
    
    default:

        break;
    }
}


