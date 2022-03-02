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

