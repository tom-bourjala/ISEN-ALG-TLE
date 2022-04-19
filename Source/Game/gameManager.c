
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "selection.h"
#include "../UI/UI_loading.h"
#include "../UI/UI_mainMenu.h"
#include "../UI/UI_hud.h"

void launchMainMenu(void *GAME){
    UI_initMainMenu(GAME);
}

void launchEndlessMode(void *GAME){
    Game *game = GAME;
    Selection *selection = game->selection;
    int mapId = 0;
    if(selection->type == SELECT_MAP){
        mapId = selection->selected.mapId;
    }
    float progress = 0.0f;
    launchLoading(GAME, &progress, "Loading Endless Mode");
    game->mapManager->loadMap("debug", 1920, 1080, &progress);
    endLoading(GAME);
    UI_initHud(GAME);
}