#include "UI_button.h"
#include "../Game/game.h"
#include <stdbool.h>

UI_button *UI_newButton(UI_menu *menu, char *text, UI_anchor *anchor, void (*onClick)(void *entry)){
    UI_button *newButton = malloc(sizeof(UI_button));
    SDL_Color white = {255,255,255,255};
    newButton->text = UI_newText(menu, text, anchor, UI_TA_LEFT, UI_TJ_UP, white, "./assets/fonts/Kubasta.ttf", 10);
    Game *game = menu->game;
    newButton->hidden = false;
    newButton->menu = menu;
    newButton->textureIdle = game->textureManager->getTexture("b_default_idle.png");
    newButton->textureHover = game->textureManager->getTexture("b_default_hover.png");
    newButton->texturePress = game->textureManager->getTexture("b_default_press.png");
    newButton->textureObject = UI_newStaticTextureObject(menu, (SDL_Rect) {0,0,0,0}, anchor, "b_default_idle.png");
    newButton->actionArea = UI_newActionArea(menu, (SDL_Rect) {0,0,0,0}, anchor, onClick);
    newButton->actionArea->disabled = true;
    newButton->anchor = anchor;
    appendInList(menu->buttons, newButton);
    return newButton;
}

void UI_updateButton(void *self){
    UI_button *this = self;
    Game *game = this->menu->game;
    
    int texHeight, texWidth;
    SDL_QueryTexture(this->textureObject->texture, NULL, NULL, &texWidth, &texHeight);
    this->textureObject->rect = (SDL_Rect) {this->anchor->getX(game), this->anchor->getY(game), texWidth*2, texHeight*2};
    this->actionArea->rect = (SDL_Rect) {this->anchor->getX(game), this->anchor->getY(game), texWidth*2, texHeight*2};
    if(this->isPressed)
        this->textureObject->texture = this->texturePress;
    else if((game->mouseX >= this->actionArea->rect.x && game->mouseX <= this->actionArea->rect.x+this->actionArea->rect.w) && (game->mouseY >= this->actionArea->rect.y && game->mouseY <= this->actionArea->rect.y+this->actionArea->rect.h))
        this->textureObject->texture = this->textureHover;
    else this->textureObject->texture = this->textureIdle;
}

void UI_ButtonHandleMouseEvent(UI_button *button, bool isDown){
    Game *game = button->menu->game;
    int x = game->mouseX;
    int y = game->mouseY;
    if(!button->hidden)
        if((x>=button->actionArea->rect.x && x<=button->actionArea->rect.x+button->actionArea->rect.w) && (y>=button->actionArea->rect.y && y<=button->actionArea->rect.y+button->actionArea->rect.h)){
            printf("BUTTON %s\n", isDown ? "DOWN" : "UP");
            if(isDown) button->isPressed = true;
            if(!isDown && button->isPressed) button->actionArea->onClick(button);
        }
    if(!isDown) button->isPressed = false;
}

void UI_FreeButton(void *self){
    UI_button *this = self;
    free(this);
}