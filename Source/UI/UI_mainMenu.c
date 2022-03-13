#include "UI_mainMenu.h"
#include "../Game/game.h"
#include <stdbool.h>

int getx_middle(void *GAME){
    Game *game = GAME;
    int wW, wH;
    SDL_GetWindowSize(game->window, &wW, &wH);
    return wW/2;
}

int gety_middle(void *GAME){
    Game *game = GAME;
    int wW, wH;
    SDL_GetWindowSize(game->window, &wW, &wH);
    return wH/2;
}

int getx_up(void *GAME){
    return getx_middle(GAME);
}

int gety_up(void *GAME){
    return gety_middle(GAME) - 200;
}

int getx_down(void *GAME){
    return getx_middle(GAME);
}

int gety_down(void *GAME){
    return gety_middle(GAME) + 200;
}

void onClickPrintf(void *self){
    printf("CLICK ON %p\n", self);
}

int zero(void *GAME){
    return 0;
}

void UI_initMainMenu(void *GAME)
{
    Game *game = GAME;
    game->menu = UI_initMenu(GAME);
    UI_anchor *A_UP = UI_newAnchor(game->menu, getx_up, gety_up);
    UI_anchor *A_MIDDLE = UI_newAnchor(game->menu, getx_middle, gety_middle);
    UI_anchor *A_DOWN = UI_newAnchor(game->menu, getx_down, gety_down);
    UI_anchor *ZZ = UI_newAnchor(game->menu, zero, zero);
    char ***textPtr = malloc(sizeof(char*));
    *textPtr = malloc(sizeof(char*));
    **textPtr = malloc(sizeof(char) * 255);
    strcpy(**textPtr, "test");
    UI_panel *newPanel = UI_newPanel(game->menu,500,500,A_UP,3,UI_PT_A);
    // newPanel->isHidden = true;
    newPanel->isActive = true;
    SDL_Rect rect = {20,20,100,200};
    char string[]="test";
    UI_newButtonPanel(newPanel,*textPtr,rect,A_MIDDLE,0);
    // UI_newStaticTextureObject(game->menu, (SDL_Rect) {0,0,1920,1080}, ZZ, "menu_background.png");
    // UI_newButton(game->menu, *textPtr, UI_B_BIG, A_UP, false, onClickPrintf, NULL, NULL, 3)->isDisabled = true;
    // UI_newButton(game->menu, *textPtr, UI_CHECK_SMALL, A_UP, false, onClickPrintf, NULL, NULL)->isDisabled = true;
    // UI_newButton(game->menu, *textPtr, UI_B_BIG, A_MIDDLE, true, onClickPrintf, NULL, NULL, 3);

    // // UI_newButton(game->menu, *textPtr, UI_BT_MIDE, A_MIDDLE, onClickPrintf);
    // UI_newButton(game->menu, *textPtr, UI_BT_LONG, A_DOWN, onClickPrintf);
    float *value = malloc(sizeof(float));
    *value = 0.5;
    //UI_newSlider(game->menu, value, 40, 3, A_MIDDLE, true, onClickPrintf);
    // // UI_newSwitch(game->menu, A_MIDDLE, onClickPrintf, onClickPrintf);
}