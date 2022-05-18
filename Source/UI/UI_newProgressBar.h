#include "UI.h"
#include "../Game/game.h"
#include "../Core/core.h"

typedef struct UI_progressBar
{
    int width;
    int height;
    SDL_Texture *front_texture;
    SDL_Texture *behind_texture;
    UI_anchor *anchor;
    float percentage;
    float *maxValue;
    float *currentValue;
    bool vertical;
    int sizeFactor;
    UI_menu *menu;
    SDL_Texture *textureDisabled;
    bool hidden;
    Game *game;
}UI_progressBar;

UI_progressBar *UI_newProgressBar(Game *game,int width,int height,char *behindTexture, char *frontTexture,UI_anchor *anchor,int sizeFactor,bool vertical,float *currentValue,float *maxValue);
void UI_renderProgressBars(UI_progressBar *progressBar);
void UI_updateProgressBars(UI_progressBar *progressBar);
void UI_FreeProgressBars(UI_progressBar *progressBar);