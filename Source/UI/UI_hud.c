#include "UI_mainMenu.h"
#include "../Game/game.h"
#include "UI_settingsMenu.h"
#include <stdbool.h>

static Game *THIS_GAME = NULL;

static char **(*LM_getTradById)(char *idToGet) = NULL;

static void onUpdate(){

}

void UI_initHud(void *GAME)
{
    THIS_GAME = GAME;
    Game *game = GAME;
    game->menu = UI_initMenu(GAME);
    game->menu->updateScript = onUpdate;
    LM_getTradById = game->languageManager->getTradById;
}