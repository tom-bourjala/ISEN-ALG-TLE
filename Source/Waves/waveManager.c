#include "./waveManager.h"
#include "./waveGenerator.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void WM_nextWave(){
    
}

waveManager *initWaveManager(void *game){
    waveManager *manager = malloc(sizeof(waveManager));
    manager->currentWave = NULL;
    manager->parent = game;
    manager->isWaveActive = false;
    manager->waveNumber = 0;
    manager->difficulty = 0.1;
    return manager;
}



