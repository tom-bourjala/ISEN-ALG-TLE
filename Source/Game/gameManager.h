#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct gameModeData
{
    int currencyA;
    int currencyB;
    int currencyC;
} gameModeData;

void updateGameManager();
void launchMainMenu(void *GAME);
void launchEndlessMode(void *GAME);

void updateCurrentGameState(void *GAME);