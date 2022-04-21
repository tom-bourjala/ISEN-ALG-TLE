
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "selection.h"
#include "../UI/UI_loading.h"
#include "../UI/UI_mainMenu.h"
#include "../UI/UI_hud.h"
#include "../Core/core.h"

void launchMainMenu(void *GAME){
    UI_initMainMenu(GAME);
}

static GameObject *Core = NULL;

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
    Core = newGameObject_Core(game, game->mapManager->currentMap->end, 100, 100, 10, 5);
    appendInList(game->gameObjects, Core);
    endLoading(GAME);
    UI_initHud(GAME);
}

void updateGameManager(){
    if(Core){
        hitCore(Core, 1);
    }
}