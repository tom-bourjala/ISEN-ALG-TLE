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
static SDL_Texture *background = NULL;
static UI_textureObject *menuLogo = NULL;

static int logo_x(void *none){return game->winWidth-700;} 
static int logo_y(void *none){return game->winHeight/2-100;} 

static int NULL_x(void *none){return 0;}
static int NULL_y(void *none){return 0;}

static int continue_x(void *none){return 220;}
static int continue_y(void *none){return game->winHeight/2-150;}

static int settings_x(void *none){return 220;}
static int settings_y(void *none){return game->winHeight/2;}

static int quit_x(void *none){return 220;}
static int quit_y(void *none){return game->winHeight/2+150;}

static int title_x(void *none){return game->winWidth/2;}
static int title_y(void *none){return 70;}

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
    forEach(game->animationManager->animList, freeAnimation);
    game->projectileManager->empty();
    game->mapManager->unloadMap();
    game->pause = false;
    WM_killWave();
    UI_initMainMenu(game);
}

void pauseInit(void *g)
{
    game = g;
    LM_getTradById = game->languageManager->getTradById;
    pause_menu = UI_initMenu(game);
    
    //UI_anchor *a = UI_newAnchor(pause_menu,logo_x,NULL_y);
    //pauseBackground = UI_newStaticTextureObjectStatic(pause_menu,(SDL_Rect){0,0,game->winWidth,game->winHeight},a,NULL);

    UI_anchor *title_anchor = UI_newAnchor(pause_menu,title_x,title_y);
    UI_text *title = UI_newText(pause_menu,LM_getTradById("PAUSE"),title_anchor,UI_TA_CENTER,UI_TJ_CENTER,(SDL_Color){255,255,255,255},"./assets/fonts/RulerGold.ttf",80);

    UI_anchor *anchor_continue = UI_newAnchor(pause_menu,continue_x,continue_y);
    UI_button *button_continue =  UI_newButton(pause_menu,LM_getTradById("pause_continue"),UI_B_BIG,anchor_continue,false,clickContinue,NULL,NULL,2);

    UI_anchor *anchor_settings = UI_newAnchor(pause_menu,settings_x,settings_y);
    UI_button *button_settings =  UI_newButton(pause_menu,LM_getTradById("pause_settings"),UI_B_BIG,anchor_settings,false,clickSettings,NULL,NULL,2);

    UI_anchor *anchor_quit = UI_newAnchor(pause_menu,quit_x,quit_y);
    UI_button *button_quit =  UI_newButton(pause_menu,LM_getTradById("pause_quit"),UI_B_BIG,anchor_quit,false,clickQuit,NULL,NULL,2);
    
    UI_anchor *a_logo = UI_newAnchor(pause_menu,logo_x,logo_y);
    menuLogo = UI_newStaticTextureObject(pause_menu, (SDL_Rect) {400,400,400,200}, a_logo, "TLELogo.png");

}

void catchPause()
{
    hud = game->menu;
    game->menu = pause_menu;
    
    SDL_PixelFormatEnum format = SDL_PIXELFORMAT_RGBA8888;
    if(background)free(background);
    background = SDL_CreateTexture(game->renderer, format, SDL_TEXTUREACCESS_TARGET,game->winWidth,game->winHeight);
    SDL_SetRenderTarget(game->renderer, background);
    SDL_SetTextureAlphaMod(background, 128);
    game->pause = false;
    game->render();
    game->pause = true;
    SDL_SetRenderTarget(game->renderer, NULL);
    UI_refreshMenu(game->menu);
    //pauseBackground->texture = background;
}

void throwPause()
{
    game->menu = hud;
    UI_refreshMenu(game->menu);
    hud = NULL;
}
