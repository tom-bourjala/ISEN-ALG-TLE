#include "UI.h"
#include <stdbool.h>

UI_button *UI_newButton(UI_menu *menu,char *text, UI_anchor *anchor, void (*onClick)(void *entry));
void UI_updateButton(void *self);
void UI_ButtonHandleMouseEvent(UI_button *button, bool isDown);
void UI_FreeButton(void *self);
