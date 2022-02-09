#include "UI_manager.h"
#include "../Game/game.h"
#include <stdbool.h>

UI_menu *MENU = NULL;

void UI_MenuUpdate(){
    //Update Textures
    forEach(MENU->textureObjects, UI_UpdateTextureObject);
    //Update Action Area
    forEach(MENU->actionAreas, UI_UpdateActionArea);
    //Update Text
    forEach(MENU->texts, UI_UpdateText);
    //Update Buttons
    forEach(MENU->buttons, UI_updateButton);
    //Update Sliders
}

void UI_MenuClear(){
    //Free Anchors
    forEach(MENU->anchors, UI_FreeAnchor);
    emptyList(MENU->anchors);
    free(MENU->anchors);
    //Free TextureObjects
    forEach(MENU->textureObjects, UI_FreeTextureObject);
    emptyList(MENU->textureObjects);
    free(MENU->textureObjects);
    //Free Action Area
    forEach(MENU->actionAreas, UI_FreeActionArea);
    emptyList(MENU->actionAreas);
    free(MENU->actionAreas);
    //Free Text
    forEach(MENU->texts, UI_FreeText);
    emptyList(MENU->texts);
    free(MENU->texts);
    //Free Buttons
    forEach(MENU->buttons, UI_FreeButton);
    emptyList(MENU->buttons);
    free(MENU->buttons);

    free(MENU);
}

void UI_MenuHandleEvent(bool isDown){
    for(int index = 0; index < MENU->actionAreas->length; index++){
        UI_actionArea *area = getDataAtIndex(*MENU->actionAreas, index);
        UI_actionAreaHandleMouseEvent(area, isDown); 
    }
    for(int index = 0; index < MENU->buttons->length; index++){
        UI_button *button = getDataAtIndex(*MENU->buttons, index);
        UI_ButtonHandleMouseEvent(button, isDown); 
    }
}

void UI_MenuRender(){
    forEach(MENU->textureObjects, UI_RenderTextureObject);
    forEach(MENU->texts, UI_RenderText);
}

UI_menu *UI_initMenu(void *game){
    UI_menu *newMenu = malloc(sizeof(UI_menu));
    newMenu->game = game;
    newMenu->update = UI_MenuUpdate;
    newMenu->clear = UI_MenuClear;
    newMenu->handleEvent = UI_MenuHandleEvent;
    newMenu->render = UI_MenuRender;
    newMenu->buttons = newList(COMPARE_PTR);
    newMenu->sliders = newList(COMPARE_PTR);
    newMenu->texts = newList(COMPARE_PTR);
    newMenu->actionAreas = newList(COMPARE_PTR);
    newMenu->textureObjects = newList(COMPARE_PTR);
    newMenu->anchors = newList(COMPARE_PTR);
    MENU = newMenu;
    return newMenu;
}