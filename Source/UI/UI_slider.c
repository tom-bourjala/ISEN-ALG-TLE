#include "UI_slider.h"
#include "../Game/game.h"



UI_Slider *UI_newSlider(UI_menu *menu, float *value, int width,float unitWidth,float unitHeight,float sizeCoef, UI_anchor *anchorCL, bool updateOnRelease, void (*onUpdate)(void *entry))
{
    UI_Slider *newSlider = malloc(sizeof(UI_Slider));
    newSlider->value = value;
    newSlider->width = width;
    newSlider->unitWidth = unitWidth;
    newSlider->unitHeight = unitHeight;
    newSlider->sizeCoef = sizeCoef;
    newSlider->anchorCL = anchorCL;
    newSlider->updateOnRelease = updateOnRelease;
    newSlider->onUpdate = onUpdate;
    newSlider->hidden = false;
    newSlider->isPressed = false;
    newSlider->menu = menu;
    appendInList(menu->sliders, newSlider);
    return newSlider;
}

void UI_updateSlider(void *self){
    UI_Slider *slider = self;
    Game *game = slider->menu->game;
    int getX = slider->anchorCL->getX(game);
    if(slider->isPressed == true)
    {  
        float totalWidth = (slider->width+2)*slider->unitWidth*slider->sizeCoef;
        if(game->mouseX <= getX)
            *slider->value=0.0;
        else if(game->mouseX >= totalWidth+getX)
        {
            *slider->value=1.0;
        }
        else
        {
            *slider->value = (game->mouseX-getX) / totalWidth;
        }
    }
}

void UI_renderSlider(void *self){
    UI_Slider *this = self;
    Game *game = this->menu->game;
    int x = this->anchorCL->getX(game);
    int y = this->anchorCL->getY(game) - ((float) 1/2)*this->unitHeight*this->sizeCoef;
    SDL_Texture *leftChunkTex = game->textureManager->getTexture("s_left.png"); 
    SDL_Texture *unitChunkTex = game->textureManager->getTexture("s_cell.png");
    SDL_Texture *rightChunkTex = game->textureManager->getTexture("s_right.png");
    SDL_Rect left = {x, y, this->unitWidth*this->sizeCoef, this->unitHeight*this->sizeCoef};
    SDL_RenderCopy(game->renderer, leftChunkTex, NULL, &left);
    for(int i = 0; i < this->width; i++){
        SDL_Rect unit = {x + this->unitWidth*this->sizeCoef*(i+1), y, this->unitWidth*this->sizeCoef, this->unitHeight*this->sizeCoef};
        SDL_RenderCopy(game->renderer, unitChunkTex, NULL, &unit);
    }
    SDL_Rect right = {x+this->unitHeight*this->width, y, this->unitWidth*this->sizeCoef, this->unitHeight*this->sizeCoef};
    SDL_RenderCopy(game->renderer, rightChunkTex, NULL, &right);
    
}

void UI_SliderHandleMouseEvent(UI_Slider *slider, bool isPressed){
    Game *game = slider->menu->game;
    if(isPressed)
    {
        float totalWidth = (slider->width+2)*slider->unitWidth*slider->sizeCoef;
        if((game->mouseX >= slider->anchorCL->getX(game) && game->mouseX <= slider->anchorCL->getX(game)+totalWidth) && (game->mouseY>=slider->anchorCL->getY(game)-5 && game->mouseY<=slider->anchorCL->getY(game)+5))
        {
            slider->isPressed = true;
        }
    }
    else
    {
        slider->isPressed = false;
    }
}

void UI_FreeSlider(void *self){
    UI_Slider *slider = self;
    free(slider);
}