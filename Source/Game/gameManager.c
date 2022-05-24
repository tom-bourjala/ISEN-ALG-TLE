
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include "selection.h"
#include "../UI/UI_loading.h"
#include "../UI/UI_mainMenu.h"
#include "../UI/UI_hud.h"
#include "../Core/core.h"
#include "../Robots/robots.h"
#include "../List/SmartList.h"

static Game *GAME = NULL;
 
void launchMainMenu(void *game){
    GAME = game;
    UI_initMainMenu(game);
}

static GameObject *Core = NULL;

void launchEndlessMode(void *game){
    GAME = game;
    Selection *selection = GAME->selection;
    int mapId = 0;
    if(selection->type == SELECT_MAP){
        mapId = selection->selected.mapId;
    }
    float progress = 0.0f;
    launchLoading(GAME, &progress, "Loading Endless Mode");
    GAME->mapManager->loadMap("debug", 1920, 1080, &progress);
    Core = newGameObject_Core(GAME, GAME->mapManager->currentMap->end, 100, 100, 500, 0.5);
    endLoading(GAME);
    UI_initHud(GAME);
    GAME->cameraScale = 0.7f;
    map_node *startNode = GAME->mapManager->currentMap->starts->first->data;
    cameraCheckSize();
}

void updateGameManager(){
    if(Core){
        core *coreActor = Core->actor;
    }
}