#include "UI_panel.h"
#include "../Game/game.h"

void getPanelKey(UI_panelType type , char *str){
    switch (type)
    {
        case UI_PT_A:
            strcpy(str, "A");
            break;
        case UI_PT_B:
            strcpy(str, "B");
            break;
    }
}

UI_panel *UI_newPanel(UI_menu *menu, int width, int height, UI_anchor *anchorLT, int sizeFactor, UI_panelType type)
{
    UI_panel *newPanel = malloc(sizeof(UI_panel));
    Game *game = (Game*)menu->game;
    newPanel->width = width;
    newPanel->height = height;
    newPanel->anchorLT = anchorLT;
    newPanel->sizeFactor = sizeFactor;
    newPanel->menu = menu;
    newPanel->isDisabled = false;
    newPanel->isActive = false;
    newPanel->isHidden = false;
    if(type==UI_PT_DIAG)
    {
        newPanel->textureIdle = game->textureManager->getTexture("UI_panel_slide.png");
        newPanel->textureEnabled = NULL;
        newPanel->textureDisabled = NULL;
        newPanel->textureCurrent = newPanel->textureIdle;
    }
    else
    {
        char id[200];
        getPanelKey(type,id);
        char idle[255];
        char enabled[255];
        char disabled[255];
        sprintf(idle,"UI_panel_%s.png",id);
        sprintf(enabled,"UI_panel_%s_enabled.png",id);
        sprintf(disabled,"UI_panel_%s_disabled.png",id);
        newPanel->textureIdle = game->textureManager->getTexture(idle);
        newPanel->textureEnabled = game->textureManager->getTexture(enabled);
        newPanel->textureDisabled = game->textureManager->getTexture(disabled);
        newPanel->textureCurrent = NULL;
    }
    appendInList(menu->panels, newPanel);
    return newPanel;
}

void UI_updatePanel(void *self){
    UI_panel *this = self;
    Game *game = this->menu->game;
    if(this->isDisabled)
        this->textureCurrent = this->textureDisabled;
    else if(this->isActive)
        this->textureCurrent = this->textureEnabled;
    else
        this->textureCurrent = this->textureIdle;
}

void UI_renderPanel(void *self){
    UI_panel *this = self;
    Game *game = this->menu->game;
    if(!this->isHidden){
        int x = this->anchorLT->getX(game);
        int y = this->anchorLT->getY(game);
 
        SDL_Rect src_rect = (SDL_Rect){7,7,2,2};
        SDL_Rect dst_rect = (SDL_Rect){x,y,this->width,this->height};
        SDL_RenderCopy(game->renderer, this->textureCurrent, &src_rect,&dst_rect);
        
        int z=8*this->sizeFactor;

        dst_rect=(SDL_Rect){x,y,this->width,z};
        src_rect=(SDL_Rect){7,0,2,8};
        SDL_RenderCopy(game->renderer, this->textureCurrent,&src_rect,&dst_rect);
        
        dst_rect=(SDL_Rect){x+this->width-z,y,z,this->height};
        src_rect=(SDL_Rect){8,7,8,2};
        SDL_RenderCopy(game->renderer, this->textureCurrent,&src_rect,&dst_rect);
        
        dst_rect=(SDL_Rect){x,y+this->height-z,this->width,z};
        src_rect=(SDL_Rect){7,8,2,8};
        SDL_RenderCopy(game->renderer, this->textureCurrent,&src_rect,&dst_rect);
        
        dst_rect=(SDL_Rect){x,y,z,this->height};
        src_rect=(SDL_Rect){0,7,8,2};
        SDL_RenderCopy(game->renderer, this->textureCurrent,&src_rect,&dst_rect);

        dst_rect = (SDL_Rect){x,y,z,z};
        src_rect = (SDL_Rect){0,0,8,8};
        SDL_RenderCopy(game->renderer, this->textureCurrent,&src_rect,&dst_rect);

        dst_rect = (SDL_Rect){x+this->width-z,y,z,z};
        src_rect = (SDL_Rect){8,0,8,8};
        SDL_RenderCopy(game->renderer, this->textureCurrent,&src_rect,&dst_rect);
        
        dst_rect = (SDL_Rect){x,y+this->height-z,z,z};
        src_rect = (SDL_Rect){0,8,8,8};
        SDL_RenderCopy(game->renderer, this->textureCurrent,&src_rect,&dst_rect);

        dst_rect = (SDL_Rect){x+this->width-z,y+this->height-z,z,z};
        src_rect = (SDL_Rect){8,8,8,8};
        SDL_RenderCopy(game->renderer, this->textureCurrent,&src_rect,&dst_rect);
        
    }
}

void UI_FreePanel(void *self){
    UI_panel *this = self;
    free(this);
}


UI_panelButton *UI_newButtonPanel(UI_panel *parent,SDL_Rect rect,int orientation)
{
    UI_panelButton *newButtonPanel = (UI_panelButton*) malloc(sizeof(UI_panelButton));
    Game *game = parent->menu->game;
    newButtonPanel->isDisabled = false;
    newButtonPanel->isActive = false;
    newButtonPanel->isHover = false;
    newButtonPanel->isHidden = false;
    newButtonPanel->rect = rect;
    newButtonPanel->orientation = orientation;
    newButtonPanel->sizeFactor = parent->sizeFactor;
    newButtonPanel->parent = parent;
    newButtonPanel->textureIdle = game->textureManager->getTexture("UI_tab_idle.png");
    newButtonPanel->textureEnabled = game->textureManager->getTexture("UI_tab_enabled.png");
    newButtonPanel->textureDisabled = game->textureManager->getTexture("UI_tab_disabled.png");
    newButtonPanel->textureCurrent = NULL;
    appendInList(parent->menu->panelButtons,newButtonPanel);
    return newButtonPanel;
}

SDL_Rect getPanelButtonRect(UI_panelButton panelButton)
{
    Game *game = panelButton.parent->menu->game;
    int Ax = panelButton.parent->anchorLT->getX(game);
    int Ay = panelButton.parent->anchorLT->getY(game);
    SDL_Rect pRect;
    switch(panelButton.orientation)
    {
        case 0:
            pRect.x = Ax + panelButton.rect.x;
            pRect.y = Ay - panelButton.rect.h + panelButton.sizeFactor;
            pRect.h = panelButton.rect.h;
            pRect.w = panelButton.rect.w;
            break;
        case 1:
            pRect.x = Ax + panelButton.parent->width - panelButton.sizeFactor;
            pRect.y = Ay + panelButton.rect.x;
            pRect.h = panelButton.rect.w;
            pRect.w = panelButton.rect.h;
            break;
        case 2:
            pRect.x = Ax + panelButton.rect.x;
            pRect.y = Ay + panelButton.parent->height - panelButton.sizeFactor;
            pRect.h = panelButton.rect.h;
            pRect.w = panelButton.rect.w;
            break;
        case 3:
            pRect.x = Ax - panelButton.rect.h + panelButton.sizeFactor;
            pRect.y = Ay + panelButton.rect.x;
            pRect.h = panelButton.rect.w;
            pRect.w = panelButton.rect.h;
            break;
    }
    return pRect;
}
void UI_updateButtonPanel(void *self){
    UI_panelButton *this = self;
    Game *game = (Game*)this->parent->menu->game;

    if(!this->isHidden){ 
        if(!this->isDisabled){
            SDL_Rect pRect = getPanelButtonRect(*this);
            bool isHover = (game->mouseX >= pRect.x && game->mouseX <= pRect.x+pRect.w) && (game->mouseY >= pRect.y && game->mouseY <= pRect.y+pRect.h);
            if(isHover)
                game->currentCursor = game->cursorHand;
        }
        if(this->isActive) this->textureCurrent = this->textureEnabled;
        else if(this->isDisabled) this->textureCurrent = this->textureDisabled;
        else this->textureCurrent = this->textureIdle;
    }
}

void UI_renderButtonPanel(void *self)
{
    UI_panelButton *this = self;
    Game *game = this->parent->menu->game;
    if(!this->isHidden){
        int x = this->parent->anchorLT->getX(game);
        int y = this->parent->anchorLT->getY(game);
 
        SDL_Rect pRect = getPanelButtonRect(*this);
        SDL_Rect src_rect = (SDL_Rect){7,7,2,2};
        SDL_Rect dst_rect = pRect;
        float angle;
        switch(this->orientation)
        {
            case 0:
                dst_rect.h = pRect.h - this->sizeFactor;
                angle = 0;
                break;
            case 1:
                dst_rect.x = pRect.x + this->sizeFactor;
                dst_rect.w = pRect.w - this->sizeFactor;
                angle = -M_PI/2;
                break;
            case 2:
                dst_rect.y = pRect.y + this->sizeFactor;
                dst_rect.h = pRect.h - this->sizeFactor;
                angle = M_PI;
                break;
            case 3:
                dst_rect.x = pRect.x - this->sizeFactor;
                angle = M_PI/2;
                break;
        }
        SDL_RenderCopy(game->renderer, this->textureCurrent, &src_rect,&dst_rect);
        int z=8*this->sizeFactor;

        dst_rect=(SDL_Rect){pRect.x,pRect.y,pRect.w,z};
        src_rect=(SDL_Rect){7,0,2,8};
        SDL_RenderCopyEx(game->renderer, this->textureCurrent,&src_rect,&dst_rect,angle,NULL,0);
        
        dst_rect=(SDL_Rect){pRect.x+pRect.w-z,pRect.y,z,pRect.h};
        src_rect=(SDL_Rect){8,7,8,2};
        SDL_RenderCopyEx(game->renderer, this->textureCurrent,&src_rect,&dst_rect,angle,NULL,0);
        
        dst_rect=(SDL_Rect){pRect.x,pRect.y+pRect.h-z,pRect.w,z};
        src_rect=(SDL_Rect){7,8,2,8};
        SDL_RenderCopyEx(game->renderer, this->textureCurrent,&src_rect,&dst_rect,angle,NULL,0);
        
        dst_rect=(SDL_Rect){pRect.x,pRect.y,z,pRect.h};
        src_rect=(SDL_Rect){0,7,8,2};
        SDL_RenderCopyEx(game->renderer, this->textureCurrent,&src_rect,&dst_rect,angle,NULL,0);

        dst_rect = (SDL_Rect){pRect.x,pRect.y,z,z};
        src_rect = (SDL_Rect){0,0,8,8};
        SDL_RenderCopyEx(game->renderer, this->textureCurrent,&src_rect,&dst_rect,angle,NULL,0);

        dst_rect = (SDL_Rect){pRect.x+pRect.w-z,pRect.y,z,z};
        src_rect = (SDL_Rect){8,0,8,8};
        SDL_RenderCopyEx(game->renderer, this->textureCurrent,&src_rect,&dst_rect,angle,NULL,0);
        
        dst_rect = (SDL_Rect){pRect.x,pRect.y+pRect.h-z,z,z};
        src_rect = (SDL_Rect){0,8,8,8};
        SDL_RenderCopyEx(game->renderer, this->textureCurrent,&src_rect,&dst_rect,angle,NULL,0);

        dst_rect = (SDL_Rect){pRect.x+pRect.w-z,pRect.y+pRect.h-z,z,z};
        src_rect = (SDL_Rect){8,8,8,8};
        SDL_RenderCopyEx(game->renderer, this->textureCurrent,&src_rect,&dst_rect,angle,NULL,0);
        
    }
}

void UI_FreeButtonPanel(void *self){
    UI_panelButton *this = self;
    free(this);
}

void UI_panelButtonHandleMouseEvent(UI_panelButton *buttonPanel, bool isDown)
{
    Game *game = buttonPanel->parent->menu->game;
    int x = game->mouseX;
    int y = game->mouseY;
    SDL_Rect pRect = getPanelButtonRect(*buttonPanel);
    bool isHover = (game->mouseX >= pRect.x && game->mouseX <= pRect.x+pRect.w) && (game->mouseY >= pRect.y && game->mouseY <= pRect.y+pRect.h);

    if(!buttonPanel->isHidden && !buttonPanel->isDisabled){
        if(!isDown && isHover){
            buttonPanel->isActive = !buttonPanel->isActive;
            // TODO : implement switching tab actions
            //if(buttonPanel->onSetOn && buttonPanel->isActive) buttonPanel->onSetOn(buttonPanel); 
            //if(buttonPanel->onSetOff && !buttonPanel->isActive) buttonPanel->onSetOff(buttonPanel);
        }
}
}
