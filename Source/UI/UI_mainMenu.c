#include "UI_mainMenu.h"
#include "../Game/game.h"
#include <stdbool.h>

static Game *THIS_GAME = NULL;

static UI_button *playButton = NULL;
static UI_button *settingsButton = NULL;
static UI_button *quitButton = NULL;
static UI_button *aboutButton = NULL;
static UI_button *campaignButton = NULL;
static UI_button *endlessButton = NULL;
static UI_button *sandboxButton = NULL;
static UI_button *backButton = NULL;

int A_RNULL(void *GAME){return 0;}
int getx_middle(void *GAME){Game *game = GAME; return game->winWidth/2 + 500;}
int gety_middle(void *GAME){Game *game = GAME; return game->winHeight/2 + 500;}

const int menuInBetween = 100;

int gety_top(void *GAME){return gety_middle(GAME) - menuInBetween;}
int gety_bottom(void *GAME){return gety_middle(GAME) + menuInBetween;}

int gety_firstInRow(void *GAME){return gety_middle(GAME) - (2 * menuInBetween);}
int gety_secondInRow(void *GAME){return gety_middle(GAME) - menuInBetween;}
int gety_thirdInRow(void *GAME){return gety_middle(GAME);}
int gety_bottomOfRow(void *GAME){return gety_middle(GAME) + (2*menuInBetween);}

void onClickPrintf(void *self){
    printf("CLICK ON %p\n", self);
}


static UI_textureObject *menuBackground = NULL;
char **(*LM_getTradById)(char *idToGet) = NULL;

void rescaleBackground(){
    int w = 1920;
    int h = 1080;
    float wRatio = THIS_GAME->winWidth / (float) w;
    float hRatio = THIS_GAME->winHeight / (float) h;
    if(h * wRatio >= THIS_GAME->winHeight){
        menuBackground->rect.w = w * wRatio;
        menuBackground->rect.h = h * wRatio;
    }else{
        menuBackground->rect.w = w * hRatio;
        menuBackground->rect.h = h * hRatio;
    }
    // printf("%d, %d", getx_middle(THIS_GAME), gety_middle(THIS_GAME));
}

void onUpdate(){
    rescaleBackground();
}

void UI_initMainMenu(void *GAME)
{
    THIS_GAME = GAME;
    Game *game = GAME;
    game->menu = UI_initMenu(GAME);
    game->menu->update = onUpdate;
    game->menu->game = GAME;
    LM_getTradById = game->languageManager->getTradById;

    UI_anchor *A_NULL = UI_newAnchor(game->menu, A_RNULL, A_RNULL);

    UI_anchor *AH_PLAY = UI_newAnchor(game->menu, A_RNULL, gety_top);
    UI_anchor *AH_SETTINGS = UI_newAnchor(game->menu, A_RNULL, gety_middle);
    UI_anchor *AH_QUIT = UI_newAnchor(game->menu, A_RNULL, gety_bottom);
    UI_anchor *AH_MIDLE = UI_newAnchor(game->menu, getx_middle, gety_middle);
    // UI_anchor *AH_ABOUT = UI_newAnchor(game->menu, ?, ?);

    UI_anchor *AP_CAMPAIGN = UI_newAnchor(game->menu, A_RNULL, gety_firstInRow);
    UI_anchor *AP_ENDLESS = UI_newAnchor(game->menu, A_RNULL, gety_secondInRow);
    UI_anchor *AP_SANDBOX = UI_newAnchor(game->menu, A_RNULL, gety_thirdInRow);
    UI_anchor *AP_BACK = UI_newAnchor(game->menu, A_RNULL, gety_bottomOfRow);

    //Main menu buttons
    playButton = UI_newButton(THIS_GAME->menu, LM_getTradById("menu_home_play"), UI_B_MAIN, AH_MIDLE, false, onClickPrintf, NULL, NULL, 3);
    // settingsButton = UI_newButton(THIS_GAME->menu, LM_getTradById("menu_home_settings"), UI_BT_MAIN, AH_SETTINGS, false, onClickPrintf, NULL, NULL, 3);
    // quitButton = UI_newButton(THIS_GAME->menu, LM_getTradById("menu_home_quit"), UI_BT_MAIN, AH_QUIT, false, onClickPrintf, NULL, NULL, 3);
    // aboutButton = UI_newButton(THIS_GAME->menu, LM_getTradById("menu_home_about"), UI_BT_MAIN, AH_ABOUT, false, onClickPrintf, NULL, NULL, 3);

    //Play menu buttons
    // campaignButton = UI_newButton(THIS_GAME->menu, LM_getTradById("menu_home_campagin"), UI_BT_MAIN, AP_CAMPAIGN, false, onClickPrintf, NULL, NULL, 3);
    // endlessButton = UI_newButton(THIS_GAME->menu, LM_getTradById("menu_home_endless"), UI_BT_MAIN, AP_ENDLESS, false, onClickPrintf, NULL, NULL, 3);
    // sandboxButton = UI_newButton(THIS_GAME->menu, LM_getTradById("menu_home_sandbox"), UI_BT_MAIN, AP_SANDBOX, false, onClickPrintf, NULL, NULL, 3);
    // backButton = UI_newButton(THIS_GAME->menu, LM_getTradById("menu_back"), UI_BT_BACK, AP_BACK, false, onClickPrintf, NULL, NULL, 3);

    menuBackground = UI_newStaticTextureObject(game->menu, (SDL_Rect) {0,0,1920,1080}, A_NULL, "menu_background.png");
    // menuBackground->hidden = true;
}