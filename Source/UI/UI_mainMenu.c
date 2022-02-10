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
    strcpy(**textPtr, "OK");
    UI_newStaticTextureObject(game->menu, (SDL_Rect) {0,0,1920,1080}, ZZ, "menu_background.png");
    UI_newButton(game->menu, *textPtr, UI_BT_SQUARE, A_UP, onClickPrintf);
    UI_newButton(game->menu, *textPtr, UI_BT_MIDE, A_MIDDLE, onClickPrintf);
    UI_newButton(game->menu, *textPtr, UI_BT_LONG, A_DOWN, onClickPrintf);
    // UI_newSwitch(game->menu, A_MIDDLE, onClickPrintf, onClickPrintf);
}