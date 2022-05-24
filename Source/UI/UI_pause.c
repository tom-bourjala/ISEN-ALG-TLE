#include <stdlib.h>
#include "UI_pause.h"
#include "../Game/game.h"
#include "UI_settingsMenu.h"
#include "UI_mainMenu.h"

static char** (*LM_getTradById)(char *idToGet) = NULL;
static UI_menu *pause_menu = NULL; 
static UI_menu *hud = NULL;
static Game *game = NULL;
static UI_textureObject *pauseBackground = NULL;

static int continue_x(void *none){return game->winWidth/2;}
static int continue_y(void *none){return 200;}

static int settings_x(void *none){return game->winWidth/2;}
static int settings_y(void *none){return game->winHeight/2;}

static int quit_x(void *none){return game->winWidth/2;}
static int quit_y(void *none){return game->winHeight-200;}

void clickContinue(void *self)
{
    throwPause();
    game->pause = false;
}

void clickSettings(void *self)
{
    UI_switchToSettings(game);
}

void clickQuit(void *self)
{
    forEach(game->gameObjects, deleteGameObject);
    game->projectileManager->empty();
    game->mapManager->unloadMap();
    game->pause = false;
    UI_initMainMenu(game);
}

void pauseInit(void *g)
{
    game = g;
    LM_getTradById = game->languageManager->getTradById;
    pause_menu = UI_initMenu(game);
    UI_anchor *anchor_continue = UI_newAnchor(pause_menu,continue_x,continue_y);
    UI_button *button_continue =  UI_newButton(pause_menu,LM_getTradById("pause_continue"),UI_B_LONG,anchor_continue,false,clickContinue,NULL,NULL,4);

    UI_anchor *anchor_settings = UI_newAnchor(pause_menu,settings_x,settings_y);
    UI_button *button_settings =  UI_newButton(pause_menu,LM_getTradById("pause_settings"),UI_B_LONG,anchor_settings,false,clickSettings,NULL,NULL,4);

    UI_anchor *anchor_quit = UI_newAnchor(pause_menu,quit_x,quit_y);
    UI_button *button_quit =  UI_newButton(pause_menu,LM_getTradById("pause_quit"),UI_B_LONG,anchor_quit,false,clickQuit,NULL,NULL,4);


}

void catchPause()
{
    hud = game->menu;
    game->menu = pause_menu;
    UI_refreshMenu(game->menu);

    
}

void throwPause()
{
    game->menu = hud;
    UI_refreshMenu(game->menu);
    hud = NULL;
}
