#include "UI_mainMenu.h"
#include "../Game/game.h"
#include "../Game/selection.h"
#include "UI_settingsMenu.h"
#include <stdbool.h>
#include "../Core/core.h"
#include "../Turrets/turrets.h"

static Game *THIS_GAME = NULL;

static char **(*LM_getTradById)(char *idToGet) = NULL;

/* Main HUD panel */
static UI_anchor *A_MID_HUD;
static UI_panel *HUD_mid_panel;
int HUD_panel_x(void *none){return 0;}
int HUD_panel_y(void *none){return THIS_GAME->winHeight-0.25*THIS_GAME->winHeight;}

/* Mid HUD panel */
int HUD_mid_panel_x(void *none){return THIS_GAME->winWidth/2-0.09375*THIS_GAME->winWidth;}
int HUD_mid_panel_y(void *none){return THIS_GAME->winHeight-0.25*THIS_GAME->winHeight;}

/* Speed HUD buttons */
int HUD_button_speed_1_x(void *none){return HUD_mid_panel_x(NULL)+0.0625*THIS_GAME->winWidth;}
int HUD_button_speed_1_y(void *none){return HUD_mid_panel_y(NULL)+0.0625*THIS_GAME->winHeight;}

int HUD_button_speed_2_x(void *none){return HUD_mid_panel_x(NULL)+0.09375*THIS_GAME->winWidth;}
int HUD_button_speed_2_y(void *none){return HUD_mid_panel_y(NULL)+0.0625*THIS_GAME->winHeight;}

int HUD_button_speed_3_x(void *none){return HUD_mid_panel_x(NULL)+0.125*THIS_GAME->winWidth;}
int HUD_button_speed_3_y(void *none){return HUD_mid_panel_y(NULL)+0.0625*THIS_GAME->winHeight;}

/* Wave info and Next button */
int HUD_wave_next_x(void *none){return THIS_GAME->winWidth/2;}
int HUD_wave_next_y(void *none){return HUD_mid_panel_y(NULL)+0.15*THIS_GAME->winHeight;}

int HUD_wave_info_x(void *none){return THIS_GAME->winWidth/2;}
int HUD_wave_info_y(void *none){return HUD_mid_panel_y(NULL)+0.21875*THIS_GAME->winHeight;}

/* Health and Shield bar */
static UI_anchor *A_HUD_SHIELD_BAR = NULL;
static UI_anchor *A_HUD_HEALTH_BAR = NULL;
int HUD_shield_bar_x(void *none){return HUD_mid_panel_x(NULL)+THIS_GAME->winWidth*0.015625;}
int HUD_shield_bar_y(void *none){return HUD_mid_panel_y(NULL)+THIS_GAME->winHeight*0.025;}
int HUD_health_bar_x(void *none){return HUD_mid_panel_x(NULL)+THIS_GAME->winWidth*0.153125;}
int HUD_health_bar_y(void *none){return HUD_mid_panel_y(NULL)+THIS_GAME->winHeight*0.025;}

/* Golds */
int HUD_golds_panel_x(void *none){return HUD_panel_x(NULL);}
int HUD_golds_panel_y(void *none){return HUD_panel_y(NULL);}
int HUD_text_golds_1_x(void *none){return HUD_panel_x(NULL)+THIS_GAME->winWidth*0.015625;}
int HUD_text_golds_1_y(void *none){return HUD_panel_y(NULL)+THIS_GAME->winHeight*0.0625;}
int HUD_text_golds_2_x(void *none){return HUD_panel_x(NULL)+THIS_GAME->winWidth*0.015625;}
int HUD_text_golds_2_y(void *none){return HUD_panel_y(NULL)+THIS_GAME->winHeight*0.125;}
int HUD_text_golds_3_x(void *none){return HUD_panel_x(NULL)+THIS_GAME->winWidth*0.015625;}
int HUD_text_golds_3_y(void *none){return HUD_panel_y(NULL)+THIS_GAME->winHeight*0.1875;}
int HUD_img_golds_1_x(void *none){return HUD_panel_x(NULL)+THIS_GAME->winWidth*0.078125;}
int HUD_img_golds_1_y(void *none){return HUD_panel_y(NULL)+THIS_GAME->winHeight*0.0625;}
int HUD_img_golds_2_x(void *none){return HUD_panel_x(NULL)+THIS_GAME->winWidth*0.078125;}
int HUD_img_golds_2_y(void *none){return HUD_panel_y(NULL)+THIS_GAME->winHeight*0.125;}
int HUD_img_golds_3_x(void *none){return HUD_panel_x(NULL)+THIS_GAME->winWidth*0.078125;}
int HUD_img_golds_3_y(void *none){return HUD_panel_y(NULL)+THIS_GAME->winHeight*0.1875;}

/* Turret Selection */
int HUD_turret_panel_1_x(void *none){return HUD_panel_x(NULL)+THIS_GAME->winWidth*0.121875;}
int HUD_turret_panel_1_y(void *none){return HUD_panel_y(NULL)+THIS_GAME->winHeight*0.04375;}
int HUD_turret_panel_2_x(void *none){return HUD_panel_x(NULL)+THIS_GAME->winWidth*0.215625;}
int HUD_turret_panel_2_y(void *none){return HUD_panel_y(NULL)+THIS_GAME->winHeight*0.04375;}
int HUD_turret_panel_3_x(void *none){return HUD_panel_x(NULL)+THIS_GAME->winWidth*0.309375;}
int HUD_turret_panel_3_y(void *none){return HUD_panel_y(NULL)+THIS_GAME->winHeight*0.04375;}
int HUD_turret_text_1_x(void *none){return HUD_panel_x(NULL)+0.15625*THIS_GAME->winWidth;}
int HUD_turret_text_1_y(void *none){return HUD_panel_y(NULL)+0.2*THIS_GAME->winHeight;}
int HUD_turret_text_2_x(void *none){return HUD_panel_x(NULL)+0.25*THIS_GAME->winWidth;}
int HUD_turret_text_2_y(void *none){return HUD_panel_y(NULL)+0.2*THIS_GAME->winHeight;}
int HUD_turret_text_3_x(void *none){return HUD_panel_x(NULL)+0.34375*THIS_GAME->winWidth;}
int HUD_turret_text_3_y(void *none){return HUD_panel_y(NULL)+0.2*THIS_GAME->winHeight;}

list *HUD_turret_list = NULL;


/* HUD right part */
int HUD_right_part_panel_x(void *none){return THIS_GAME->winWidth-0.39375*THIS_GAME->winWidth;}
int HUD_right_part_panel_y(void *none){return HUD_panel_y(NULL)+0.025*THIS_GAME->winHeight;}
int HUD_right_part_title_x(void *none){return HUD_right_part_panel_x(NULL)+0.0125*THIS_GAME->winWidth;}
int HUD_right_part_title_y(void *none){return HUD_right_part_panel_y(NULL)+0.0375*THIS_GAME->winHeight;}
int HUD_right_part_img_x(void *none){return HUD_right_part_panel_x(NULL)+0.0125*THIS_GAME->winWidth;}
int HUD_right_part_img_y(void *none){return HUD_right_part_panel_y(NULL)+0.05625*THIS_GAME->winHeight;}
int HUD_right_part_text_1_x(void *none){return HUD_right_part_img_x(NULL)+0.095*THIS_GAME->winWidth;}
int HUD_right_part_text_1_y(void *none){return HUD_right_part_img_y(NULL)+0.025*THIS_GAME->winHeight;}
int HUD_right_part_text_2_x(void *none){return HUD_right_part_img_x(NULL)+0.095*THIS_GAME->winWidth;}
int HUD_right_part_text_2_y(void *none){return HUD_right_part_img_y(NULL)+0.0625*THIS_GAME->winHeight;}
int HUD_right_part_text_3_x(void *none){return HUD_right_part_img_x(NULL)+0.095*THIS_GAME->winWidth;}
int HUD_right_part_text_3_y(void *none){return HUD_right_part_img_y(NULL)+0.1*THIS_GAME->winHeight;}

typedef struct{
    turretSelection *turret;
    int x;
    int y;
    int width;
    int height;
    UI_actionArea *actionArea;
    UI_textureObject *texObj;
    UI_text *text;
    UI_panel *panel;
} turretSelector;

list *turretSelectors = NULL;

void changeSpeed_1(void *none)
{

}

void changeSpeed_2(void *none)
{

}

void changeSpeed_3(void *none)
{

}

void nextWave(void *none)
{

}

void eventTurretSelector(void *triggeredActionArea)
{
    turretSelector *selected = NULL;
    void getSelectedTurret(void *self){
        turretSelector *this = self;
        if(this->actionArea == triggeredActionArea){
            selected = this;
        }
    }
    forEach(turretSelectors, getSelectedTurret);
    if(selected){
        if(THIS_GAME->selection){
            Selection *currentSelection = THIS_GAME->selection;
            if(currentSelection->type == SELECT_TURRET){
                turretSelection *currentTurret = currentSelection->selected.turretSelection; 
                if(currentTurret == selected->turret){
                    free(currentSelection);
                    THIS_GAME->selection = NULL;
                    return;
                }
            }
            free(currentSelection);
            THIS_GAME->selection = NULL;
        }
        Selection *selection = malloc(sizeof(Selection));
        selection->type = SELECT_TURRET;
        selection->selected.turretSelection = selected->turret;
        THIS_GAME->selection = selection;
    }
}

static void onUpdate(){

}

void displayShieldBar()
{
    UI_panel *panel = UI_newPanel(THIS_GAME->menu,0.01875*THIS_GAME->winWidth,THIS_GAME->winHeight*0.2, A_HUD_SHIELD_BAR, 2, UI_PT_A);
    core *ThisCore = THIS_GAME->coreObj->actor;
    ThisCore->maxShield = 100;
    ThisCore->shield = 75;
    float percentage = (float)(ThisCore->health/ThisCore->maxHealth);
    UI_panel *shield = UI_newPanel(THIS_GAME->menu,0.01875*THIS_GAME->winWidth,THIS_GAME->winHeight*0.2, A_HUD_SHIELD_BAR, 2, UI_PT_A);
    shield->isActive = true;

}

void displayHealthBar()
{
    UI_panel *panel = UI_newPanel(THIS_GAME->menu,0.01875*THIS_GAME->winWidth,THIS_GAME->winHeight*0.2, A_HUD_HEALTH_BAR, 2, UI_PT_A);
    core *ThisCore = THIS_GAME->coreObj->actor;
    ThisCore->maxShield = 100;
    ThisCore->shield = 75;
    float percentage = (float)(ThisCore->health/ThisCore->maxHealth);
    
    UI_panel *health = UI_newPanel(THIS_GAME->menu,0.01875*THIS_GAME->winWidth, 0.2*THIS_GAME->winHeight, A_HUD_HEALTH_BAR, 2, UI_PT_A);
    health->isActive = true;
}

void UI_initHud(void *GAME)
{
    THIS_GAME = GAME;
    Game *game = GAME;
    game->menu = UI_initMenu(GAME);
    game->menu->updateScript = onUpdate;
    LM_getTradById = game->languageManager->getTradById;

    /* Main HUD panel */
    UI_anchor *A_HUD = UI_newAnchor(game->menu, HUD_panel_x, HUD_panel_y);
    UI_panel *HUD_panel = UI_newPanel(game->menu, game->winWidth, 0.25*THIS_GAME->winHeight, A_HUD, 2, UI_PT_A);
    
    /* Mid HUD panel */
    A_MID_HUD = UI_newAnchor(game->menu, HUD_mid_panel_x, HUD_mid_panel_y);
    HUD_mid_panel = UI_newPanel(game->menu, 0.1875*THIS_GAME->winWidth, 0.25*THIS_GAME->winHeight, A_MID_HUD, 2, UI_PT_A);
    HUD_mid_panel->isActive = true;

    /* Speed HUD buttons */
    float speed_size_factor = (THIS_GAME->winWidth > 1200) ? 1.5 : 1.15;
    UI_anchor *A_SPEED_1_HUD = UI_newAnchor(game->menu, HUD_button_speed_1_x, HUD_button_speed_1_y);
    UI_button *HUD_button_speed_1 = UI_newButton(HUD_mid_panel->menu, NULL, UI_ARROW,A_SPEED_1_HUD,false,changeSpeed_1,NULL,NULL,speed_size_factor);
    UI_flipButton(HUD_button_speed_1,SDL_FLIP_HORIZONTAL);
    UI_anchor *A_SPEED_2_HUD = UI_newAnchor(game->menu, HUD_button_speed_2_x, HUD_button_speed_2_y);
    UI_button *HUD_button_speed_2 = UI_newButton(HUD_mid_panel->menu, NULL, UI_ARROW,A_SPEED_2_HUD,false,changeSpeed_2,NULL,NULL,speed_size_factor);
    UI_flipButton(HUD_button_speed_2,SDL_FLIP_HORIZONTAL);
    UI_anchor *A_SPEED_3_HUD = UI_newAnchor(game->menu, HUD_button_speed_3_x, HUD_button_speed_3_y);
    UI_button *HUD_button_speed_3 = UI_newButton(HUD_mid_panel->menu, NULL, UI_ARROW,A_SPEED_3_HUD,false,changeSpeed_3,NULL,NULL,speed_size_factor);
    UI_flipButton(HUD_button_speed_3,SDL_FLIP_HORIZONTAL);

    /* Wave info and Next button */
    int next_font_size = (THIS_GAME->winWidth > 1200) ? 30 : 25;
    float next_size_factor = (THIS_GAME->winWidth > 1200) ? 1.7 : 1.4;
    UI_anchor *A_WAVE_NEXT_HUD = UI_newAnchor(game->menu, HUD_wave_next_x, HUD_wave_next_y);
    UI_button *HUD_button_wave_next = UI_newButton(HUD_mid_panel->menu,LM_getTradById("hud_next_wave"), UI_B_LONG,A_WAVE_NEXT_HUD,false,nextWave,NULL,NULL,next_size_factor);
    UI_anchor *A_WAVE_INFO_HUD = UI_newAnchor(game->menu, HUD_wave_info_x, HUD_wave_info_y);
    UI_text *HUD_text_wave_info = UI_newText(game->menu,LM_getTradById("hud_wave_info"),A_WAVE_INFO_HUD, UI_TA_CENTER, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", next_font_size);
    
    /* Health and Shield bar */
    A_HUD_SHIELD_BAR = UI_newAnchor(game->menu, HUD_shield_bar_x, HUD_shield_bar_y);
    A_HUD_HEALTH_BAR = UI_newAnchor(game->menu, HUD_health_bar_x, HUD_health_bar_y);
    displayHealthBar();
    displayShieldBar();

    /* Golds */
    UI_anchor *A_PANEL_GOLDS_HUD = UI_newAnchor(game->menu, HUD_golds_panel_x, HUD_golds_panel_y);
    UI_panel *HUD_golds_panel = UI_newPanel(game->menu,0.103125*THIS_GAME->winWidth,0.25*THIS_GAME->winHeight, A_PANEL_GOLDS_HUD, 2, UI_PT_A);
    HUD_golds_panel->isActive = true;

    UI_anchor *A_TEXT_GOLDS_HUD_1 = UI_newAnchor(game->menu, HUD_text_golds_1_x, HUD_text_golds_1_y);
    char **text_golds_1 = malloc(sizeof(char*));
    *text_golds_1 = malloc(sizeof(char)*10);
    int font_size = (THIS_GAME->winWidth > 1200) ? 30 : 25;
    strcpy(*text_golds_1,"9999");
    UI_text *HUD_text_golds_1 = UI_newText(game->menu,text_golds_1,A_TEXT_GOLDS_HUD_1, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", font_size);
    UI_anchor *A_IMG_GOLDS_HUD_1 = UI_newAnchor(game->menu, HUD_img_golds_1_x, HUD_img_golds_1_y);
    UI_button *HUD_img_golds_1 = UI_newButton(game->menu, NULL, UI_ARROW,A_IMG_GOLDS_HUD_1,false,changeSpeed_1,NULL,NULL,1);

    UI_anchor *A_TEXT_GOLDS_HUD_2 = UI_newAnchor(game->menu, HUD_text_golds_2_x, HUD_text_golds_2_y);
    char **text_golds_2 = malloc(sizeof(char*));
    *text_golds_2 = malloc(sizeof(char)*10);
    strcpy(*text_golds_2,"1234");
    UI_text *HUD_text_golds_2 = UI_newText(game->menu,text_golds_2,A_TEXT_GOLDS_HUD_2, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", font_size);
    UI_anchor *A_IMG_GOLDS_HUD_2 = UI_newAnchor(game->menu, HUD_img_golds_2_x, HUD_img_golds_2_y);
    UI_button *HUD_img_golds_2 = UI_newButton(game->menu, NULL, UI_ARROW,A_IMG_GOLDS_HUD_2,false,changeSpeed_1,NULL,NULL,1);

    UI_anchor *A_TEXT_GOLDS_HUD_3 = UI_newAnchor(game->menu, HUD_text_golds_3_x, HUD_text_golds_3_y);
    char **text_golds_3 = malloc(sizeof(char*));
    *text_golds_3 = malloc(sizeof(char)*10);
    strcpy(*text_golds_3,"7891");
    UI_text *HUD_text_golds_3 = UI_newText(game->menu,text_golds_3,A_TEXT_GOLDS_HUD_3, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", font_size);
    UI_anchor *A_IMG_GOLDS_HUD_3 = UI_newAnchor(game->menu, HUD_img_golds_3_x, HUD_img_golds_3_y);
    UI_button *HUD_img_golds_3 = UI_newButton(game->menu, NULL, UI_ARROW,A_IMG_GOLDS_HUD_3,false,changeSpeed_1,NULL,NULL,1);

    /* Turret Selection*/
    UI_anchor *A_PANEL_TURRET_HUD_1 = UI_newAnchor(game->menu, HUD_turret_panel_1_x, HUD_turret_panel_1_y);
    UI_anchor *A_PANEL_TURRET_HUD_2 = UI_newAnchor(game->menu, HUD_turret_panel_2_x, HUD_turret_panel_2_y);
    UI_anchor *A_PANEL_TURRET_HUD_3 = UI_newAnchor(game->menu, HUD_turret_panel_3_x, HUD_turret_panel_3_y);
    UI_panel *HUD_turret_panel_1 = UI_newPanel(game->menu,0.125*THIS_GAME->winHeight,0.125*THIS_GAME->winHeight, A_PANEL_TURRET_HUD_1, 2, UI_PT_A);
    UI_panel *HUD_turret_panel_2 = UI_newPanel(game->menu,0.125*THIS_GAME->winHeight,0.125*THIS_GAME->winHeight, A_PANEL_TURRET_HUD_2, 2, UI_PT_A);
    UI_panel *HUD_turret_panel_3 = UI_newPanel(game->menu,0.125*THIS_GAME->winHeight,0.125*THIS_GAME->winHeight, A_PANEL_TURRET_HUD_3, 2, UI_PT_A);

    UI_anchor *A_TEXT_TURRET_HUD_1 = UI_newAnchor(game->menu, HUD_turret_text_1_x, HUD_turret_text_1_y);
    UI_anchor *A_TEXT_TURRET_HUD_2 = UI_newAnchor(game->menu, HUD_turret_text_2_x, HUD_turret_text_2_y);
    UI_anchor *A_TEXT_TURRET_HUD_3 = UI_newAnchor(game->menu, HUD_turret_text_3_x, HUD_turret_text_3_y);

    HUD_turret_list = generateTurretsSelection(game);
    turretSelectors = newList(COMPARE_PTR);
    for(int i = 0; i < 3; i++){
        turretSelection *tmp = getDataAtIndex(*HUD_turret_list, i);
        if(!tmp) break;
        UI_anchor *A_text_tmp;
        UI_anchor *A_panel_tmp;
        turretSelector *tmp_selector = malloc(sizeof(turretSelector));
        switch(i){
            case 0:
                A_text_tmp = A_TEXT_TURRET_HUD_1;
                A_panel_tmp = A_PANEL_TURRET_HUD_1;
                break;
            case 1:
                A_text_tmp = A_TEXT_TURRET_HUD_2;
                A_panel_tmp = A_PANEL_TURRET_HUD_2;
                break;
            case 2:
                A_text_tmp = A_TEXT_TURRET_HUD_3;
                A_panel_tmp = A_PANEL_TURRET_HUD_3;
                break;
        }
        int width = 0.125*THIS_GAME->winHeight;
        int height = 0.125*THIS_GAME->winHeight;
        tmp_selector->text = UI_newText(game->menu,tmp->name,A_text_tmp, UI_TA_CENTER, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 20);
        tmp_selector->panel = UI_newPanel(game->menu,width,height, A_panel_tmp, 2, UI_PT_A);
        tmp_selector->actionArea = UI_newActionArea(game->menu, (SDL_Rect) {0,0, width, height}, A_panel_tmp, eventTurretSelector);
        tmp_selector->texObj = UI_newStaticTextureObjectStatic(game->menu, (SDL_Rect) {0,0, width, height}, A_panel_tmp, tmp->thumbnail);
        tmp_selector->turret = tmp;
        appendInList(turretSelectors, tmp_selector);
    }

    /* HUD right part */
    UI_anchor *A_PANEL_RIGHT_PART_HUD = UI_newAnchor(game->menu, HUD_right_part_panel_x, HUD_right_part_panel_y);
    UI_panel *HUD_right_part_panel = UI_newPanel(game->menu,0.378125*THIS_GAME->winWidth,0.2*THIS_GAME->winHeight, A_PANEL_RIGHT_PART_HUD, 2, UI_PT_A);
    
    UI_anchor *A_TITLE_RIGHT_PART_HUD = UI_newAnchor(game->menu, HUD_right_part_title_x, HUD_right_part_title_y);
    char **title_right_part = malloc(sizeof(char*));
    *title_right_part = malloc(sizeof(char)*255);
    strcpy(*title_right_part,"SHIELD");
    UI_text *HUD_title_right_part = UI_newText(game->menu,title_right_part,A_TITLE_RIGHT_PART_HUD, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 30);
    
    UI_anchor *A_IMG_RIGHT_PART_HUD = UI_newAnchor(game->menu, HUD_right_part_img_x, HUD_right_part_img_y);
    UI_panel *HUD_right_part_img = UI_newPanel(game->menu,0.125*THIS_GAME->winHeight,0.125*THIS_GAME->winHeight, A_IMG_RIGHT_PART_HUD, 2, UI_PT_A);
    
    UI_anchor *A_TEXT_1_RIGHT_PART_HUD = UI_newAnchor(game->menu, HUD_right_part_text_1_x, HUD_right_part_text_1_y);
    char **text_1_right_part = malloc(sizeof(char*));
    *text_1_right_part = malloc(sizeof(char)*255);
    strcpy(*text_1_right_part,"text");
    UI_text *HUD_text_1_right_part = UI_newText(game->menu,text_1_right_part,A_TEXT_1_RIGHT_PART_HUD, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 30);
    UI_anchor *A_TEXT_2_RIGHT_PART_HUD = UI_newAnchor(game->menu, HUD_right_part_text_2_x, HUD_right_part_text_2_y);
    char **text_2_right_part = malloc(sizeof(char*));
    *text_2_right_part = malloc(sizeof(char)*255);
    strcpy(*text_2_right_part,"text");
    UI_text *HUD_text_2_right_part = UI_newText(game->menu,text_2_right_part,A_TEXT_2_RIGHT_PART_HUD, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 30);
    UI_anchor *A_TEXT_3_RIGHT_PART_HUD = UI_newAnchor(game->menu, HUD_right_part_text_3_x, HUD_right_part_text_3_y);
    char **text_3_right_part = malloc(sizeof(char*));
    *text_3_right_part = malloc(sizeof(char)*255);
    strcpy(*text_3_right_part,"text");
    UI_text *HUD_text_3_right_part = UI_newText(game->menu,text_3_right_part,A_TEXT_3_RIGHT_PART_HUD, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 30);
    
}