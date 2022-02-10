#include "UI.h"
#include <stdbool.h>

UI_button *UI_newButton(UI_menu *menu,char **text, UI_buttonType type, UI_anchor *anchor, void (*onClick)(void *entry));
UI_button *UI_newSwitch(UI_menu *menu, UI_anchor *anchor, void (*onSetOn)(void *entry), void (*onSetOff)(void *entry));
void UI_updateButton(void *self);
void UI_ButtonHandleMouseEvent(UI_button *button, bool isDown);
void UI_FreeButton(void *self);
