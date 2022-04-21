#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct gameModeData
{
    int currencyA;
    int currencyB;
    int currencyC;
    int wave;
    int waveMax;
    bool isPaused;
} gameModeData;


void launchMainMenu(void *GAME);
void launchEndlessMode(void *GAME);

void updateCurrentGameState(void *GAME);