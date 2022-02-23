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
    forEach(MENU->sliders, UI_updateSlider);
}

void UI_MenuClear(){
    //Free Anchors
    forEach(MENU->anchors, UI_FreeAnchor);
    freeList(MENU->anchors);
    //Free TextureObjects
    forEach(MENU->textureObjects, UI_FreeTextureObject);
    freeList(MENU->textureObjects);
    //Free Action Area
    forEach(MENU->actionAreas, UI_FreeActionArea);
    freeList(MENU->actionAreas);
    //Free Text
    forEach(MENU->texts, UI_FreeText);
    freeList(MENU->texts);
    //Free Buttons
    forEach(MENU->buttons, UI_FreeButton);
    freeList(MENU->buttons);
    //Free Sliders
    forEach(MENU->sliders, UI_FreeSlider);
    freeList(MENU->sliders);
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
    for(int index = 0; index < MENU->sliders->length; index++){
        UI_slider *slider = getDataAtIndex(*MENU->sliders, index);
        UI_SliderHandleMouseEvent(slider, isDown); 
    }
}

void UI_MenuRender(){
    forEach(MENU->textureObjects, UI_RenderTextureObject);
    forEach(MENU->texts, UI_RenderText);
    forEach(MENU->sliders, UI_renderSlider);
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