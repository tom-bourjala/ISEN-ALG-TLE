#include "UI_slider.h"
#include "../Game/game.h"



UI_slider *UI_newSlider(UI_menu *menu, float *value, int width, float sizeCoef, UI_anchor *anchorCL, bool updateOnRelease, void (*onUpdate)(void *entry))
{
    UI_slider *newSlider = malloc(sizeof(UI_slider));
    newSlider->value = value;
    newSlider->width = width;
    newSlider->unitWidth = 3;
    newSlider->unitHeight = 8;
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
    UI_slider *slider = self;
    Game *game = slider->menu->game;
    int getX = slider->anchorCL->getX(game);
    float totalWidth = (slider->width+1)*slider->unitWidth*slider->sizeCoef;
    if(slider->isPressed == true)
    {  
        if(game->mouseX <= getX) *slider->value=0.0;
        else if(game->mouseX >= totalWidth+getX) *slider->value=1.0;
        else *slider->value = (game->mouseX-getX) / totalWidth;
    }
    if((game->mouseX >= slider->anchorCL->getX(game) && game->mouseX <= slider->anchorCL->getX(game)+totalWidth) && (game->mouseY>=slider->anchorCL->getY(game)-(5*slider->sizeCoef) && game->mouseY<=slider->anchorCL->getY(game)+(5*slider->sizeCoef)))
        game->currentCursor = game->cursorHand;
}

void UI_renderSlider(void *self){
    UI_slider *this = self;
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
    SDL_Rect right = {x+this->unitWidth*(this->width+1)*this->sizeCoef, y, this->unitWidth*this->sizeCoef, this->unitHeight*this->sizeCoef};
    SDL_RenderCopy(game->renderer, rightChunkTex, NULL, &right);
    SDL_Texture *buttonTex = game->textureManager->getTexture("s_button.png");
    float totalWidth = (this->width+1)*this->unitWidth*this->sizeCoef;
    SDL_Rect button = {x - 10 + (totalWidth * *this->value), y - 10, 11*this->sizeCoef, 15*this->sizeCoef};
    SDL_RenderCopy(game->renderer, buttonTex, NULL, &button);
}

void UI_SliderHandleMouseEvent(UI_slider *slider, bool isPressed){
    Game *game = slider->menu->game;
    if(isPressed)
    {
        float totalWidth = (slider->width+1)*slider->unitWidth*slider->sizeCoef;
        if((game->mouseX >= slider->anchorCL->getX(game) && game->mouseX <= slider->anchorCL->getX(game)+totalWidth) && (game->mouseY>=slider->anchorCL->getY(game)-(5*slider->sizeCoef) && game->mouseY<=slider->anchorCL->getY(game)+(5*slider->sizeCoef)))
            slider->isPressed = true;
    }
    else slider->isPressed = false;
}

void UI_FreeSlider(void *self){
    UI_slider *slider = self;
    free(slider);
}