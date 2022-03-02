#include "UI_struct.h"

UI_panel *UI_newPanel(UI_menu *menu, int width, int height, UI_anchor *anchorLT, int sizeFactor, UI_panelType type);
UI_buttonPanel *UI_newButtonPanel(UI_menu *menu,SDL_Rect rect,int orientation, int sizeFactor);
void UI_updatePanel(void *self);
void UI_updateButtonPanel(void *self);
void UI_panelButtonHandleMouseEvent(UI_buttonPanel *buttonPanel, bool isDown);
void UI_renderButtonPanel(void *self);
void UI_renderPanel(void *self);
void UI_FreePanel(void *self);