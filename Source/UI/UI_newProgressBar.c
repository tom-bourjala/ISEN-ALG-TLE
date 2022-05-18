#include "UI_newProgressBar.h"

static float percentage = 0;

UI_progressBar *UI_newProgressBar(Game *game,int width,int height,char *behindTexture, char *frontTexture,UI_anchor *anchor,int sizeFactor,bool vertical,float *currentValue,float *maxValue)
{
    UI_progressBar *progressBar = malloc(sizeof(UI_progressBar));
    progressBar->menu = game->menu;
    progressBar->game = game;
    progressBar->hidden = false;
    if(!vertical)
    {
        progressBar->width = height;
        progressBar->height = width;
    }
    progressBar->width = width;
    progressBar->height = height;
    progressBar->currentValue = currentValue;
    progressBar->maxValue = maxValue;
    progressBar->percentage = (float)(*progressBar->currentValue)/(float)(*progressBar->maxValue);
    char id[200];
    getPanelKey(UI_PT_A,id);
    char idle[255];
    char enabled[255];
    char disabled[255];
    sprintf(idle,"UI_panel_%s.png",id);
    sprintf(enabled,"UI_panel_%s_enabled.png",id);
    sprintf(disabled,"UI_panel_%s_disabled.png",id);
    progressBar->behind_texture = game->textureManager->getTexture(idle);
    progressBar->front_texture = game->textureManager->getTexture(enabled);
    progressBar->textureDisabled = game->textureManager->getTexture(disabled);
    progressBar->anchor = anchor;
    progressBar->vertical = vertical;
    progressBar->sizeFactor = sizeFactor;
    UI_updateProgressBars(progressBar);
    appendInList(game->menu->progressBars, progressBar);
    return progressBar; 
}

void UI_updateProgressBars(UI_progressBar *progressBar)
{
    progressBar->percentage = (float)(*progressBar->currentValue)/(float)(*progressBar->maxValue);
}

void UI_renderProgressBars(UI_progressBar *progressBar){
    Game *game = progressBar->menu->game;
    UI_progressBar *this = progressBar;
    if(!this->hidden){
        if(!this->vertical)
        {
            int temp = this->width;
            this->width = this->height;
            this->height = temp;
        }
        int x = this->anchor->getX(game);
        int y = this->anchor->getY(game);
 
        SDL_Rect src_rect = (SDL_Rect){7,7,2,2};
        SDL_Rect dst_rect = (SDL_Rect){x,y,this->width,this->height};
        SDL_RenderCopy(game->renderer, this->behind_texture, &src_rect,&dst_rect);
        
        int z=8*this->sizeFactor;

        dst_rect=(SDL_Rect){x,y,this->width,z};
        src_rect=(SDL_Rect){7,0,2,8};
        SDL_RenderCopy(game->renderer, this->behind_texture,&src_rect,&dst_rect);
        
        dst_rect=(SDL_Rect){x+this->width-z,y,z,this->height};
        src_rect=(SDL_Rect){8,7,8,2};
        SDL_RenderCopy(game->renderer, this->behind_texture,&src_rect,&dst_rect);
        
        dst_rect=(SDL_Rect){x,y+this->height-z,this->width,z};
        src_rect=(SDL_Rect){7,8,2,8};
        SDL_RenderCopy(game->renderer, this->behind_texture,&src_rect,&dst_rect);
        
        dst_rect=(SDL_Rect){x,y,z,this->height};
        src_rect=(SDL_Rect){0,7,8,2};
        SDL_RenderCopy(game->renderer, this->behind_texture,&src_rect,&dst_rect);

        dst_rect = (SDL_Rect){x,y,z,z};
        src_rect = (SDL_Rect){0,0,8,8};
        SDL_RenderCopy(game->renderer, this->behind_texture,&src_rect,&dst_rect);

        dst_rect = (SDL_Rect){x+this->width-z,y,z,z};
        src_rect = (SDL_Rect){8,0,8,8};
        SDL_RenderCopy(game->renderer, this->behind_texture,&src_rect,&dst_rect);
        
        dst_rect = (SDL_Rect){x,y+this->height-z,z,z};
        src_rect = (SDL_Rect){0,8,8,8};
        SDL_RenderCopy(game->renderer, this->behind_texture,&src_rect,&dst_rect);

        dst_rect = (SDL_Rect){x+this->width-z,y+this->height-z,z,z};
        src_rect = (SDL_Rect){8,8,8,8};
        SDL_RenderCopy(game->renderer, this->behind_texture,&src_rect,&dst_rect);

        //-----------------------------------------------------------------------------
        if(this->vertical)
        {
            src_rect = (SDL_Rect){7,7,2,2};
            dst_rect = (SDL_Rect){x,y+this->height*(1-this->percentage),this->width,this->height*this->percentage};
            SDL_RenderCopy(game->renderer, this->front_texture, &src_rect,&dst_rect);

            dst_rect=(SDL_Rect){x,y+this->height*(1-this->percentage),this->width,z*this->percentage};
            src_rect=(SDL_Rect){7,0,2,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
            
            dst_rect=(SDL_Rect){x+this->width-z,y+this->height*(1-this->percentage),z,this->height*this->percentage};
            src_rect=(SDL_Rect){8,7,8,2};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
            
            dst_rect=(SDL_Rect){x,y+this->height-z,this->width,z};
            src_rect=(SDL_Rect){7,8,2,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
            
            dst_rect=(SDL_Rect){x,y+this->height*(1-this->percentage),z,this->height*this->percentage};
            src_rect=(SDL_Rect){0,7,8,2};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);

            dst_rect = (SDL_Rect){x,y+this->height*(1-this->percentage),z,z};
            src_rect = (SDL_Rect){0,0,8,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
            
            dst_rect = (SDL_Rect){x+this->width-z,y+this->height*(1-this->percentage),z,z};
            src_rect = (SDL_Rect){8,0,8,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
            
            dst_rect = (SDL_Rect){x,y+this->height-z,z,z};
            src_rect = (SDL_Rect){0,8,8,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);

            dst_rect = (SDL_Rect){x+this->width-z,y+this->height-z,z,z};
            src_rect = (SDL_Rect){8,8,8,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
        }

        else
        {
            src_rect = (SDL_Rect){7,7,2,2};
            dst_rect = (SDL_Rect){x+this->width*(1-this->percentage),y,this->width*this->percentage,this->height};
            SDL_RenderCopy(game->renderer, this->front_texture, &src_rect,&dst_rect);

            dst_rect=(SDL_Rect){x+this->width*(1-this->percentage),y,this->width*this->percentage,z};
            src_rect=(SDL_Rect){7,0,2,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
            
            dst_rect=(SDL_Rect){x,y,z*this->percentage,this->height};
            src_rect=(SDL_Rect){8,7,8,2};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
            
            dst_rect=(SDL_Rect){x+this->width*(1-this->percentage),y+this->height-z,this->width*this->percentage,z};
            src_rect=(SDL_Rect){7,8,2,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
            
            dst_rect=(SDL_Rect){x+this->width*(1-this->percentage),y,z*this->percentage,this->height};
            src_rect=(SDL_Rect){0,7,8,2};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);

            dst_rect = (SDL_Rect){x+this->width*(1-this->percentage),y,z,z};
            src_rect = (SDL_Rect){0,0,8,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
            
            dst_rect = (SDL_Rect){x+this->width-z,y,z,z};
            src_rect = (SDL_Rect){8,0,8,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
            
            dst_rect = (SDL_Rect){x+this->width*(1-this->percentage),y+this->height-z,z,z};
            src_rect = (SDL_Rect){0,8,8,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);

            dst_rect = (SDL_Rect){x+this->width-z,y+this->height-z,z,z};
            src_rect = (SDL_Rect){8,8,8,8};
            SDL_RenderCopy(game->renderer, this->front_texture,&src_rect,&dst_rect);
        }
        
        if(!this->vertical)
        {
            int temp = this->width;
            this->width = this->height;
            this->height = temp;
        }
    }
}

void UI_FreeProgressBars(UI_progressBar *progressBar)
{
    free(progressBar);
}