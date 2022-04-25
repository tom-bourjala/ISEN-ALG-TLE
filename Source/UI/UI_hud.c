#include "UI_mainMenu.h"
#include "../Game/game.h"
#include "UI_settingsMenu.h"
#include <stdbool.h>
#include "../Core/core.h"

static Game *THIS_GAME = NULL;

static char **(*LM_getTradById)(char *idToGet) = NULL;

/* Main HUD panel */
static UI_anchor *A_MID_HUD;
static UI_panel *HUD_mid_panel;
int HUD_panel_x(void *none){return 0;}
int HUD_panel_y(void *none){return THIS_GAME->winHeight-200;}

/* Mid HUD panel */
int HUD_mid_panel_x(void *none){return THIS_GAME->winWidth/2-150;}
int HUD_mid_panel_y(void *none){return THIS_GAME->winHeight-200;}

/* Speed HUD buttons */
int HUD_button_speed_1_x(void *none){return HUD_mid_panel_x(NULL)+100;}
int HUD_button_speed_1_y(void *none){return HUD_mid_panel_y(NULL)+50;}

int HUD_button_speed_2_x(void *none){return HUD_mid_panel_x(NULL)+150;}
int HUD_button_speed_2_y(void *none){return HUD_mid_panel_y(NULL)+50;}

int HUD_button_speed_3_x(void *none){return HUD_mid_panel_x(NULL)+200;}
int HUD_button_speed_3_y(void *none){return HUD_mid_panel_y(NULL)+50;}

/* Wave info and Next button */
int HUD_wave_next_x(void *none){return THIS_GAME->winWidth/2;}
int HUD_wave_next_y(void *none){return HUD_mid_panel_y(NULL)+120;}

int HUD_wave_info_x(void *none){return THIS_GAME->winWidth/2;}
int HUD_wave_info_y(void *none){return HUD_mid_panel_y(NULL)+175;}

/* Health and Shield bar */
static UI_anchor *A_HUD_SHIELD_BAR = NULL;
static UI_anchor *A_HUD_HEALTH_BAR = NULL;
int HUD_shield_bar_x(void *none){return HUD_mid_panel_x(NULL)+25;}
int HUD_shield_bar_y(void *none){return HUD_mid_panel_y(NULL)+20;}
int HUD_health_bar_x(void *none){return HUD_mid_panel_x(NULL)+245;}
int HUD_health_bar_y(void *none){return HUD_mid_panel_y(NULL)+20;}

/* Golds */
int HUD_golds_panel_x(void *none){return HUD_panel_x(NULL);}
int HUD_golds_panel_y(void *none){return HUD_panel_y(NULL);}
int HUD_text_golds_1_x(void *none){return HUD_panel_x(NULL)+25;}
int HUD_text_golds_1_y(void *none){return HUD_panel_y(NULL)+50;}
int HUD_text_golds_2_x(void *none){return HUD_panel_x(NULL)+25;}
int HUD_text_golds_2_y(void *none){return HUD_panel_y(NULL)+100;}
int HUD_text_golds_3_x(void *none){return HUD_panel_x(NULL)+25;}
int HUD_text_golds_3_y(void *none){return HUD_panel_y(NULL)+150;}
int HUD_img_golds_1_x(void *none){return HUD_panel_x(NULL)+125;}
int HUD_img_golds_1_y(void *none){return HUD_panel_y(NULL)+50;}
int HUD_img_golds_2_x(void *none){return HUD_panel_x(NULL)+125;}
int HUD_img_golds_2_y(void *none){return HUD_panel_y(NULL)+100;}
int HUD_img_golds_3_x(void *none){return HUD_panel_x(NULL)+125;}
int HUD_img_golds_3_y(void *none){return HUD_panel_y(NULL)+150;}

/* Turret Selection */
int HUD_turret_panel_1_x(void *none){return HUD_panel_x(NULL)+215;}
int HUD_turret_panel_1_y(void *none){return HUD_panel_y(NULL)+35;}
int HUD_turret_panel_2_x(void *none){return HUD_panel_x(NULL)+350;}
int HUD_turret_panel_2_y(void *none){return HUD_panel_y(NULL)+35;}
int HUD_turret_panel_3_x(void *none){return HUD_panel_x(NULL)+490;}
int HUD_turret_panel_3_y(void *none){return HUD_panel_y(NULL)+35;}
int HUD_turret_text_1_x(void *none){return HUD_panel_x(NULL)+265;}
int HUD_turret_text_1_y(void *none){return HUD_panel_y(NULL)+160;}
int HUD_turret_text_2_x(void *none){return HUD_panel_x(NULL)+400;}
int HUD_turret_text_2_y(void *none){return HUD_panel_y(NULL)+160;}
int HUD_turret_text_3_x(void *none){return HUD_panel_x(NULL)+540;}
int HUD_turret_text_3_y(void *none){return HUD_panel_y(NULL)+160;}

/* HUD right part */
int HUD_right_part_panel_x(void *none){return HUD_panel_x(NULL)+970;}
int HUD_right_part_panel_y(void *none){return HUD_panel_y(NULL)+20;}
int HUD_right_part_title_x(void *none){return HUD_right_part_panel_x(NULL)+20;}
int HUD_right_part_title_y(void *none){return HUD_right_part_panel_y(NULL)+30;}
int HUD_right_part_img_x(void *none){return HUD_right_part_panel_x(NULL)+20;}
int HUD_right_part_img_y(void *none){return HUD_right_part_panel_y(NULL)+45;}
int HUD_right_part_text_1_x(void *none){return HUD_right_part_img_x(NULL)+120;}
int HUD_right_part_text_1_y(void *none){return HUD_right_part_img_y(NULL)+20;}
int HUD_right_part_text_2_x(void *none){return HUD_right_part_img_x(NULL)+120;}
int HUD_right_part_text_2_y(void *none){return HUD_right_part_img_y(NULL)+50;}
int HUD_right_part_text_3_x(void *none){return HUD_right_part_img_x(NULL)+120;}
int HUD_right_part_text_3_y(void *none){return HUD_right_part_img_y(NULL)+80;}


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

static void onUpdate(){

}

void displayShieldBar()
{
    UI_panel *panel = UI_newPanel(THIS_GAME->menu,30,160, A_HUD_SHIELD_BAR, 2, UI_PT_A);
    core *ThisCore = THIS_GAME->coreObj->actor;
    ThisCore->maxShield = 100;
    ThisCore->shield = 75;
    float percentage = (float)(ThisCore->health/ThisCore->maxHealth);
    UI_panel *shield = UI_newPanel(THIS_GAME->menu,30,160, A_HUD_SHIELD_BAR, 2, UI_PT_A);
    shield->isActive = true;

}

void displayHealthBar()
{
    UI_panel *panel = UI_newPanel(THIS_GAME->menu,30,160, A_HUD_HEALTH_BAR, 2, UI_PT_A);
    core *ThisCore = THIS_GAME->coreObj->actor;
    ThisCore->maxShield = 100;
    ThisCore->shield = 75;
    float percentage = (float)(ThisCore->health/ThisCore->maxHealth);
    
    UI_panel *health = UI_newPanel(THIS_GAME->menu,30,160, A_HUD_HEALTH_BAR, 2, UI_PT_A);
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
    UI_panel *HUD_panel = UI_newPanel(game->menu, game->winWidth, 200, A_HUD, 2, UI_PT_A);
    
    /* Mid HUD panel */
    A_MID_HUD = UI_newAnchor(game->menu, HUD_mid_panel_x, HUD_mid_panel_y);
    HUD_mid_panel = UI_newPanel(game->menu, 300, 200, A_MID_HUD, 2, UI_PT_A);
    HUD_mid_panel->isActive = true;

    /* Speed HUD buttons */
    UI_anchor *A_SPEED_1_HUD = UI_newAnchor(game->menu, HUD_button_speed_1_x, HUD_button_speed_1_y);
    UI_button *HUD_button_speed_1 = UI_newButton(HUD_mid_panel->menu, NULL, UI_ARROW,A_SPEED_1_HUD,false,changeSpeed_1,NULL,NULL,1.5);
    UI_flipButton(HUD_button_speed_1);
    UI_anchor *A_SPEED_2_HUD = UI_newAnchor(game->menu, HUD_button_speed_2_x, HUD_button_speed_2_y);
    UI_button *HUD_button_speed_2 = UI_newButton(HUD_mid_panel->menu, NULL, UI_ARROW,A_SPEED_2_HUD,false,changeSpeed_2,NULL,NULL,1.5);
    UI_flipButton(HUD_button_speed_2);
    UI_anchor *A_SPEED_3_HUD = UI_newAnchor(game->menu, HUD_button_speed_3_x, HUD_button_speed_3_y);
    UI_button *HUD_button_speed_3 = UI_newButton(HUD_mid_panel->menu, NULL, UI_ARROW,A_SPEED_3_HUD,false,changeSpeed_3,NULL,NULL,1.5);
    UI_flipButton(HUD_button_speed_3);

    /* Wave info and Next button */
    UI_anchor *A_WAVE_NEXT_HUD = UI_newAnchor(game->menu, HUD_wave_next_x, HUD_wave_next_y);
    UI_button *HUD_button_wave_next = UI_newButton(HUD_mid_panel->menu,LM_getTradById("hud_next_wave"), UI_B_DEFAULT,A_WAVE_NEXT_HUD,false,nextWave,NULL,NULL,1.7);
    UI_anchor *A_WAVE_INFO_HUD = UI_newAnchor(game->menu, HUD_wave_info_x, HUD_wave_info_y);
    UI_text *HUD_text_wave_info = UI_newText(game->menu,LM_getTradById("hud_wave_info"),A_WAVE_INFO_HUD, UI_TA_CENTER, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 30);
    
    /* Health and Shield bar */
    A_HUD_SHIELD_BAR = UI_newAnchor(game->menu, HUD_shield_bar_x, HUD_shield_bar_y);
    A_HUD_HEALTH_BAR = UI_newAnchor(game->menu, HUD_health_bar_x, HUD_health_bar_y);
    displayHealthBar();
    displayShieldBar();

    /* Golds */
    UI_anchor *A_PANEL_GOLDS_HUD = UI_newAnchor(game->menu, HUD_golds_panel_x, HUD_golds_panel_y);
    UI_panel *HUD_golds_panel = UI_newPanel(game->menu,165,200, A_PANEL_GOLDS_HUD, 2, UI_PT_A);
    HUD_golds_panel->isActive = true;

    UI_anchor *A_TEXT_GOLDS_HUD_1 = UI_newAnchor(game->menu, HUD_text_golds_1_x, HUD_text_golds_1_y);
    char **text_golds_1 = malloc(sizeof(char*));
    *text_golds_1 = malloc(sizeof(char)*10);
    strcpy(*text_golds_1,"999999");
    UI_text *HUD_text_golds_1 = UI_newText(game->menu,text_golds_1,A_TEXT_GOLDS_HUD_1, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 30);
    UI_anchor *A_IMG_GOLDS_HUD_1 = UI_newAnchor(game->menu, HUD_img_golds_1_x, HUD_img_golds_1_y);
    UI_button *HUD_img_golds_1 = UI_newButton(game->menu, NULL, UI_ARROW,A_IMG_GOLDS_HUD_1,false,changeSpeed_1,NULL,NULL,1);

    UI_anchor *A_TEXT_GOLDS_HUD_2 = UI_newAnchor(game->menu, HUD_text_golds_2_x, HUD_text_golds_2_y);
    char **text_golds_2 = malloc(sizeof(char*));
    *text_golds_2 = malloc(sizeof(char)*10);
    strcpy(*text_golds_2,"123456");
    UI_text *HUD_text_golds_2 = UI_newText(game->menu,text_golds_2,A_TEXT_GOLDS_HUD_2, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 30);
    UI_anchor *A_IMG_GOLDS_HUD_2 = UI_newAnchor(game->menu, HUD_img_golds_2_x, HUD_img_golds_2_y);
    UI_button *HUD_img_golds_2 = UI_newButton(game->menu, NULL, UI_ARROW,A_IMG_GOLDS_HUD_2,false,changeSpeed_1,NULL,NULL,1);

    UI_anchor *A_TEXT_GOLDS_HUD_3 = UI_newAnchor(game->menu, HUD_text_golds_3_x, HUD_text_golds_3_y);
    char **text_golds_3 = malloc(sizeof(char*));
    *text_golds_3 = malloc(sizeof(char)*10);
    strcpy(*text_golds_3,"789101");
    UI_text *HUD_text_golds_3 = UI_newText(game->menu,text_golds_3,A_TEXT_GOLDS_HUD_3, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 30);
    UI_anchor *A_IMG_GOLDS_HUD_3 = UI_newAnchor(game->menu, HUD_img_golds_3_x, HUD_img_golds_3_y);
    UI_button *HUD_img_golds_3 = UI_newButton(game->menu, NULL, UI_ARROW,A_IMG_GOLDS_HUD_3,false,changeSpeed_1,NULL,NULL,1);

    /* Turret Selection*/
    UI_anchor *A_PANEL_TURRET_HUD_1 = UI_newAnchor(game->menu, HUD_turret_panel_1_x, HUD_turret_panel_1_y);
    UI_panel *HUD_turret_panel_1 = UI_newPanel(game->menu,100,100, A_PANEL_TURRET_HUD_1, 2, UI_PT_A);
    UI_anchor *A_PANEL_TURRET_HUD_2 = UI_newAnchor(game->menu, HUD_turret_panel_2_x, HUD_turret_panel_2_y);
    UI_panel *HUD_turret_panel_2 = UI_newPanel(game->menu,100,100, A_PANEL_TURRET_HUD_2, 2, UI_PT_A);
    UI_anchor *A_PANEL_TURRET_HUD_3 = UI_newAnchor(game->menu, HUD_turret_panel_3_x, HUD_turret_panel_3_y);
    UI_panel *HUD_turret_panel_3 = UI_newPanel(game->menu,100,100, A_PANEL_TURRET_HUD_3, 2, UI_PT_A);

    UI_anchor *A_TEXT_TURRET_HUD_1 = UI_newAnchor(game->menu, HUD_turret_text_1_x, HUD_turret_text_1_y);
    char **text_turret_1 = malloc(sizeof(char*));
    *text_turret_1 = malloc(sizeof(char)*255);
    strcpy(*text_turret_1,"Turret name");
    UI_text *HUD_text_turret_1 = UI_newText(game->menu,text_turret_1,A_TEXT_TURRET_HUD_1, UI_TA_CENTER, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 20);
    UI_anchor *A_TEXT_TURRET_HUD_2 = UI_newAnchor(game->menu, HUD_turret_text_2_x, HUD_turret_text_2_y);
    char **text_turret_2 = malloc(sizeof(char*));
    *text_turret_2 = malloc(sizeof(char)*255);
    strcpy(*text_turret_2,"Turret name");
    UI_text *HUD_text_turret_2 = UI_newText(game->menu,text_turret_2,A_TEXT_TURRET_HUD_2, UI_TA_CENTER, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 20);
    UI_anchor *A_TEXT_TURRET_HUD_3 = UI_newAnchor(game->menu, HUD_turret_text_3_x, HUD_turret_text_3_y);
    char **text_turret_3 = malloc(sizeof(char*));
    *text_turret_3 = malloc(sizeof(char)*255);
    strcpy(*text_turret_3,"Turret name");
    UI_text *HUD_text_turret_3 = UI_newText(game->menu,text_turret_3,A_TEXT_TURRET_HUD_3, UI_TA_CENTER, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 20);
    
    /* HUD right part */
    UI_anchor *A_PANEL_RIGHT_PART_HUD = UI_newAnchor(game->menu, HUD_right_part_panel_x, HUD_right_part_panel_y);
    UI_panel *HUD_right_part_panel = UI_newPanel(game->menu,605,160, A_PANEL_RIGHT_PART_HUD, 2, UI_PT_A);
    
    UI_anchor *A_TITLE_RIGHT_PART_HUD = UI_newAnchor(game->menu, HUD_right_part_title_x, HUD_right_part_title_y);
    char **title_right_part = malloc(sizeof(char*));
    *title_right_part = malloc(sizeof(char)*255);
    strcpy(*title_right_part,"SHIELD");
    UI_text *HUD_title_right_part = UI_newText(game->menu,title_right_part,A_TITLE_RIGHT_PART_HUD, UI_TA_LEFT, UI_TJ_CENTER,(SDL_Color){255,255,255,255}, "./assets/fonts/RulerGold.ttf", 30);
    
    UI_anchor *A_IMG_RIGHT_PART_HUD = UI_newAnchor(game->menu, HUD_right_part_img_x, HUD_right_part_img_y);
    UI_panel *HUD_right_part_img = UI_newPanel(game->menu,100,100, A_IMG_RIGHT_PART_HUD, 2, UI_PT_A);
    
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