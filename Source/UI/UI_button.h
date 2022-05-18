#include "UI.h"
#include <stdbool.h>

UI_button *UI_newButton(UI_menu *menu, char **text, UI_buttonType type, UI_anchor *anchor, bool isSticky, void (*onClick)(void *button), void (*onSetOn)(void *button), void (*onSetOff)(void *button), float sizeFactor);
void UI_flipButton(UI_button *button, SDL_RendererFlip flip);
void UI_updateButton(void *self);
void UI_ButtonHandleMouseEvent(UI_button *button, bool isDown);
void UI_FreeButton(void *self);
UI_button *UI_newButtonIcon(UI_menu *menu, UI_buttonType type, UI_anchor *anchor, bool isSticky, void (*onClick)(void *button), void (*onSetOn)(void *button), void (*onSetOff)(void *button), float sizeFactor,char *icon);
void UI_setButtonIcon(UI_button *button, char *icon, SDL_RendererFlip flip);
