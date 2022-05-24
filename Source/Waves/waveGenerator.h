#pragma once
#include "./waveManager.h"

wave *generateNewWave(int waveNumber,float difficulty,waveManager *parent);
void introToVariants(int waveNumber,wave *currentWave);
void introToTanks(int waveNumber,wave *currentWave);
void introToBombers(int waveNumber,wave *currentWave);
void introToRobots(int waveNumber,wave *currentWave);
wave *newWave(waveManager *parent);
waveChunk *newChunk();
waveSpawner *newSpawner(int number,int id,int seed, map_node *spawnLocation);
map_node *getSpawnModulo(list *spawns,int spawnId);

