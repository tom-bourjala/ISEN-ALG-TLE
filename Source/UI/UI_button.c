#include "UI_button.h"
#include "../Game/game.h"
#include <stdbool.h>

UI_button *UI_newButton(UI_menu *menu, char **text, UI_buttonType type, UI_anchor *anchor, void (*onClick)(void *entry)){
    UI_button *newButton = malloc(sizeof(UI_button));
    SDL_Color white = {255,255,255,255};
    newButton->text = UI_newText(menu, text, anchor, UI_TA_CENTER, UI_TJ_CENTER, white, "./assets/fonts/Kubasta.ttf", 50);
    Game *game = menu->game;
    newButton->hidden = false;
    newButton->menu = menu;
    char idleStr[255], hoverStr[255], pressStr[255];
    switch (type)
    {
        case UI_BT_SQUARE:
            strcpy(idleStr,"b_square_idle.png");
            strcpy(hoverStr,"b_square_hover.png");
            strcpy(pressStr,"b_square_press.png");
            break;
        case UI_BT_MIDE:
            strcpy(idleStr,"b_mide_idle.png");
            strcpy(hoverStr,"b_mide_hover.png");
            strcpy(pressStr,"b_mide_press.png");
            break;
        case UI_BT_LONG:
            strcpy(idleStr,"b_long_idle.png");
            strcpy(hoverStr,"b_long_hover.png");
            strcpy(pressStr,"b_long_press.png");
            break;
        default:
            break;
    }
    newButton->textureIdle = game->textureManager->getTexture(idleStr);
    newButton->textureHover = game->textureManager->getTexture(hoverStr);
    newButton->texturePress = game->textureManager->getTexture(pressStr);                                                                                           
    newButton->textureObject = UI_newStaticTextureObject(menu, (SDL_Rect) {0,0,0,0}, anchor, idleStr);
    newButton->actionArea = UI_newActionArea(menu, (SDL_Rect) {0,0,0,0}, anchor, onClick);
    newButton->actionArea->disabled = true;
    newButton->isPressed = false;
    newButton->anchor = anchor;
    newButton->type = type;
    newButton->onSetOn = NULL;
    newButton->onSetOff = NULL;
    appendInList(menu->buttons, newButton);
    return newButton;
}

UI_button *UI_newSwitch(UI_menu *menu, UI_anchor *anchor, void (*onSetOn)(void *entry), void (*onSetOff)(void *entry)){
    UI_button *newButton = malloc(sizeof(UI_button));
    newButton->text = NULL;
    Game *game = menu->game;
    newButton->hidden = false;
    newButton->menu = menu;
    newButton->textureIdle = game->textureManager->getTexture("b_switch_off.png");
    newButton->texturePress = game->textureManager->getTexture("b_switch_on.png");
    newButton->textureObject = UI_newStaticTextureObject(menu, (SDL_Rect) {0,0,0,0}, anchor, "b_switch_off.png");
    newButton->actionArea = UI_newActionArea(menu, (SDL_Rect) {0,0,0,0}, anchor, NULL);
    newButton->actionArea->disabled = true;
    newButton->isPressed = false;
    newButton->anchor = anchor;
    newButton->type = UI_BT_SWITCH;
    newButton->onSetOn = onSetOn;
    newButton->onSetOff = onSetOff;
    appendInList(menu->buttons, newButton);
    return newButton;
}

void UI_updateButton(void *self){
    UI_button *this = self;
    Game *game = this->menu->game;
    int coefZoom = 3;
    int texHeight, texWidth;
    SDL_QueryTexture(this->textureObject->texture, NULL, NULL, &texWidth, &texHeight);
    SDL_Rect rect = (SDL_Rect) {this->anchor->getX(game) - ((texWidth*coefZoom)/2), this->anchor->getY(game) - ((texHeight*coefZoom)/2), texWidth*coefZoom, texHeight*coefZoom};
    this->textureObject->rect = rect;
    this->actionArea->rect = rect;
    bool isHover = (game->mouseX >= this->actionArea->rect.x && game->mouseX <= this->actionArea->rect.x+this->actionArea->rect.w) && (game->mouseY >= this->actionArea->rect.y && game->mouseY <= this->actionArea->rect.y+this->actionArea->rect.h);
    if(isHover) game->currentCursor = game->cursorHand;
    switch (this->type)
    {
        case UI_BT_SWITCH:
            if(this->isPressed) this->textureObject->texture = this->texturePress;
            else this->textureObject->texture = this->textureIdle;
            break;
        default:
            if(this->isPressed){
                this->textureObject->texture = this->texturePress;
                this->text->rect.y += 3*coefZoom;
            }
            else if(isHover)
                this->textureObject->texture = this->textureHover;
            else this->textureObject->texture = this->textureIdle;
            break;
    }
}

void UI_ButtonHandleMouseEvent(UI_button *button, bool isDown){
    Game *game = button->menu->game;
    int x = game->mouseX;
    int y = game->mouseY;
    bool isHover = (x>=button->actionArea->rect.x && x<=button->actionArea->rect.x+button->actionArea->rect.w) && (y>=button->actionArea->rect.y && y<=button->actionArea->rect.y+button->actionArea->rect.h);
    switch (button->type)
    {
        case UI_BT_SWITCH:
            if(!button->hidden && !isDown && isHover)
                button->isPressed = !button->isPressed;
            break;

        default:
            if(!button->hidden)
                if(isHover){
                    if(isDown) button->isPressed = true;
                    if(!isDown && button->isPressed) button->actionArea->onClick(button);
                }
            if(!isDown) button->isPressed = false;
            break;
    }
}

void UI_FreeButton(void *self){
    UI_button *this = self;
    free(this);
}