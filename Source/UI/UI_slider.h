#include "UI_struct.h"

UI_Slider *UI_newSlider(UI_menu *menu, float *value, int width, float unitWidth,float unitHeight,float sizeCoef,UI_anchor *anchorCL, bool updateOnRelease, void (*onUpdate)(void *entry));
void UI_updateSlider(void *self);
void UI_SliderHandleMouseEvent(UI_Slider *slider, bool isDown);
void UI_FreeSlider(void *self);