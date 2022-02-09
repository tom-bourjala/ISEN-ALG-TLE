#include "UI_slider.h"
#include "../Game/game.h"

void UI_newSlider(UI_menu *menu,float *value, int width, UI_anchor *anchor, void (*onUpdate)(void *entry))
{
    UI_Slider *newSlider = malloc(sizeof(UI_Slider));
    newSlider->value = value;
    newSlider->width = width;
    newSlider->anchor = anchor;
    newSlider->onUpdate = onUpdate;
    Game *game = menu->game;
}