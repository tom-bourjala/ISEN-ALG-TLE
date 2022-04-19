#include "UI_settingsMenu.h"
#include "../Game/game.h"
#include <stdbool.h>

static Game *THIS_GAME = NULL;
static UI_menu *backStateMenu = NULL;

int getLT_x(void *none){return 200;}
int getLT_y(void *none){return 100;}

//CORE PANEL
UI_panel *st_panel = NULL;
static UI_button *st_button_back = NULL;

//GENERAL PANEL
static UI_panelButton *st_button_general = NULL;
static UI_text *st_text_general_title = NULL;

//DISPLAY PANEL
static UI_panelButton *st_button_display = NULL;
static UI_text *st_text_display_title = NULL;

static UI_text *st_text_resolution = NULL;
static UI_text *st_text_fullscreen = NULL;
static UI_button *st_button_fullscreen = NULL;
static UI_slider *st_slider_resolution = NULL;

//AUDIO PANEL
static UI_panelButton *st_button_audio = NULL;
static UI_text *st_text_audio_title = NULL;

static float screen_size = 0.5;
static float master_volume = 0.5;
static float music_volume = 0.5;
static float effects_volume = 0.5;
static float dialogues_volume = 0.5;
static UI_text *st_text_master = NULL;
static UI_text *st_text_music = NULL;
static UI_text *st_text_effects = NULL;
static UI_text *st_text_dialogues = NULL;

static UI_slider *st_slider_master = NULL;
static UI_slider *st_slider_music = NULL;
static UI_slider *st_slider_effects = NULL;
static UI_slider *st_slider_dialogues = NULL;


//KEYS MAP PANEL
static UI_panelButton *st_button_commands = NULL;
static UI_text *st_text_commands_title = NULL;

//ACCESSIBILITY PANEL
static UI_panelButton *st_button_accessibility = NULL;
static UI_text *st_text_accessibility_title = NULL;

static UI_text *st_text_language = NULL;
static UI_text *st_text_daltonism = NULL;
static UI_text *st_text_screen_shake = NULL;
static UI_text *st_text_inverse_x_axis = NULL;
static UI_text *st_text_inverse_y_axis = NULL;
static UI_text *st_text_text_size = NULL;

static UI_button *st_arrow_left_lang = NULL;
static UI_button *st_arrow_right_lang = NULL;


static char **(*LM_getTradById)(char *string) = NULL;

int getPannelMiddle_x(void *none){return THIS_GAME->winWidth/2;}
int getPannelMiddle_y(void *none){return THIS_GAME->winHeight/2;}

int back_button_anchor_x(void *non){return getPannelMiddle_x(NULL)+455;}
int back_button_anchor_y(void *non){return getPannelMiddle_y(NULL)+350;}

int col_left_x(void *none){return st_panel->width/4+getLT_x(NULL);}
int col_right_x(void *none){return 2*st_panel->width/3+getLT_x(NULL);}

int st_title_x(void *none){return getLT_x(NULL)+50;}
int st_title_y(void *none){return getLT_y(NULL)+50;}

int st_text_row_1(void *none){return getPannelMiddle_y(NULL)-200;}
int st_text_row_2(void *none){return getPannelMiddle_y(NULL)-140;}
int st_text_row_3(void *none){return getPannelMiddle_y(NULL)-80;}
int st_text_row_4(void *none){return getPannelMiddle_y(NULL)-20;}
int st_text_row_5(void *none){return getPannelMiddle_y(NULL)+40;}
int st_text_row_6(void *none){return getPannelMiddle_y(NULL)+100;}
int st_text_row_7(void *none){return getPannelMiddle_y(NULL)+160;}

void changeGeneralHiddenState(bool hidden){
    st_text_general_title->hidden = hidden;
}

void changeDisplayHiddenState(bool hidden){
    st_text_display_title->hidden = hidden;
    st_text_resolution->hidden = hidden;
    st_text_fullscreen->hidden = hidden;
    st_button_fullscreen->hidden = hidden;
    st_slider_resolution->hidden = hidden;
    st_text_resolution->hidden = hidden;
}

void changeAudioHiddenState(bool hidden){
    st_text_audio_title->hidden = hidden;
    st_text_master->hidden = hidden;
    st_text_music->hidden = hidden;
    st_text_effects->hidden = hidden;
    st_text_dialogues->hidden = hidden;
    st_slider_master->hidden = hidden;
    st_slider_music->hidden = hidden;
    st_slider_effects->hidden = hidden;
    st_slider_dialogues->hidden = hidden;
}

void changeCommandsHiddenState(bool hidden){
    st_text_commands_title->hidden = hidden;
}

void changeAccessibilityHiddenState(bool hidden){
    st_text_accessibility_title->hidden = hidden;
    st_text_language->hidden = hidden;
    st_text_daltonism->hidden = hidden;
    st_text_screen_shake->hidden = hidden;
    st_text_inverse_x_axis->hidden = hidden;
    st_text_inverse_y_axis->hidden = hidden;
    st_text_text_size->hidden = hidden;
    st_arrow_left_lang->hidden = hidden;
    st_arrow_right_lang->hidden = hidden;
}

void onUpdateSettings(){
    //printf("%d x %d\n",THIS_GAME->mouseX,THIS_GAME->mouseY);
    st_panel->width = THIS_GAME->winWidth - (getLT_x(NULL)*2);
    st_panel->height = THIS_GAME->winHeight - (getLT_y(NULL)*2);

    /*int max_x,max_y;
    SDL_GetWindowMaximumSize(THIS_GAME->window,&max_x,&max_y);
    SDL_SetWindowSize(THIS_GAME->window,800+(abs(max_x-800))*(*st_slider_resolution->value),600+(abs(max_x-600))*(*st_slider_resolution->value));
    */

    changeGeneralHiddenState(!st_button_general->isActive);
    changeAccessibilityHiddenState(!st_button_accessibility->isActive);
    changeAudioHiddenState(!st_button_audio->isActive);
    changeCommandsHiddenState(!st_button_commands->isActive);
    changeDisplayHiddenState(!st_button_display->isActive);
}

void switchBack(void)
{
    THIS_GAME->menu = backStateMenu;
    UI_refreshMenu(backStateMenu);
}

void onClear(void *self){
    switchBack();
}

void onMenuSwitch(void *self)
{
    st_button_general->isActive = (self == st_button_general);
    st_button_audio->isActive = (self == st_button_audio);
    st_button_display->isActive = (self == st_button_display);
    st_button_commands->isActive = (self == st_button_commands);
    st_button_accessibility->isActive = (self == st_button_accessibility);
}

void fullscreen_on(void *self)
{
    UI_button *button = self;
    button->isPressed = true;
    SDL_SetWindowFullscreen(THIS_GAME->window,SDL_WINDOW_FULLSCREEN);
}

void fullscreen_off(void *self)
{
    UI_button *button = self;
    button->isPressed = false;
    SDL_SetWindowFullscreen(THIS_GAME->window,0);
}

void UI_switchToSettings(void *GAME)
{
    THIS_GAME = GAME;
    Game *game = GAME;
    LM_getTradById = game->languageManager->getTradById;
    backStateMenu = game->menu; // previous save
    game->menu = UI_initMenu(GAME);
    game->menu->updateScript = onUpdateSettings;
    game->menu->clearScript = onClear;
    UI_anchor *A_LC = UI_newAnchor(game->menu, getLT_x, getLT_y);
    UI_anchor *anchor_back_button = UI_newAnchor(game->menu, back_button_anchor_x,back_button_anchor_y);
    st_panel = UI_newPanel(game->menu, 0, 0, A_LC, 2, UI_PT_A);
    
    st_panel->isActive = true;
    st_button_general = UI_newButtonPanel(st_panel, LM_getTradById("menu_settings_general"), (SDL_Rect){100,0,200,50}, 0,onMenuSwitch);
    st_button_general->isActive = true;
    st_button_display = UI_newButtonPanel(st_panel, LM_getTradById("menu_settings_display"), (SDL_Rect){300,0,200,50}, 0,onMenuSwitch);
    st_button_audio = UI_newButtonPanel(st_panel, LM_getTradById("menu_settings_audio"), (SDL_Rect){500,0,200,50}, 0,onMenuSwitch);
    st_button_commands = UI_newButtonPanel(st_panel, LM_getTradById("menu_settings_commands"), (SDL_Rect){700,0,200,50}, 0,onMenuSwitch);
    st_button_accessibility = UI_newButtonPanel(st_panel, LM_getTradById("menu_settings_accessibility"), (SDL_Rect){900,0,200,50}, 0,onMenuSwitch);
    st_button_back = UI_newButton(game->menu, LM_getTradById("menu_settings_back"), UI_B_BACK,anchor_back_button,false,onClear,NULL,NULL,1);

    SDL_Color white = {255,255,255,255};
    UI_anchor *st_title_anchor = UI_newAnchor(game->menu, st_title_x, st_title_y);
    st_text_general_title = UI_newText(game->menu,LM_getTradById("menu_settings_general"),st_title_anchor, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 60);
    st_text_display_title = UI_newText(game->menu,LM_getTradById("menu_settings_display"),st_title_anchor, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 60);
    st_text_audio_title = UI_newText(game->menu,LM_getTradById("menu_settings_audio"),st_title_anchor, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 60);
    st_text_commands_title = UI_newText(game->menu,LM_getTradById("menu_settings_commands"),st_title_anchor, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 60);
    st_text_accessibility_title = UI_newText(game->menu,LM_getTradById("menu_settings_accessibility"),st_title_anchor, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 60);

    UI_anchor *st_title_line_anchor_col_left_row_1 = UI_newAnchor(game->menu, col_left_x, st_text_row_1);
    UI_anchor *st_title_line_anchor_col_left_row_2 = UI_newAnchor(game->menu, col_left_x, st_text_row_2);
    UI_anchor *st_title_line_anchor_col_left_row_3 = UI_newAnchor(game->menu, col_left_x, st_text_row_3);
    UI_anchor *st_title_line_anchor_col_left_row_4 = UI_newAnchor(game->menu, col_left_x, st_text_row_4);
    UI_anchor *st_title_line_anchor_col_left_row_5 = UI_newAnchor(game->menu, col_left_x, st_text_row_5);
    UI_anchor *st_title_line_anchor_col_left_row_6 = UI_newAnchor(game->menu, col_left_x, st_text_row_6);
    UI_anchor *st_title_line_anchor_col_left_row_7 = UI_newAnchor(game->menu, col_left_x, st_text_row_7);
    UI_anchor *st_title_line_anchor_col_right_row_1 = UI_newAnchor(game->menu, col_right_x, st_text_row_1);
    UI_anchor *st_title_line_anchor_col_right_row_2 = UI_newAnchor(game->menu, col_right_x, st_text_row_2);
    UI_anchor *st_title_line_anchor_col_right_row_3 = UI_newAnchor(game->menu, col_right_x, st_text_row_3);
    UI_anchor *st_title_line_anchor_col_right_row_4 = UI_newAnchor(game->menu, col_right_x, st_text_row_4);
    UI_anchor *st_title_line_anchor_col_right_row_5 = UI_newAnchor(game->menu, col_right_x, st_text_row_5);
    UI_anchor *st_title_line_anchor_col_right_row_6 = UI_newAnchor(game->menu, col_right_x, st_text_row_6);
    UI_anchor *st_title_line_anchor_col_right_row_7 = UI_newAnchor(game->menu, col_right_x, st_text_row_7);

    st_text_resolution = UI_newText(st_panel->menu,LM_getTradById("options_menu_video_resolution"),st_title_line_anchor_col_left_row_2, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_slider_resolution = UI_newSlider(st_panel->menu, &screen_size, 25,4,st_title_line_anchor_col_right_row_2,true,NULL);
    // a implementer

    st_text_fullscreen = UI_newText(st_panel->menu,LM_getTradById("options_menu_video_fullscreen"),st_title_line_anchor_col_left_row_3, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_button_fullscreen = UI_newButton(st_panel->menu, NULL, UI_CHECK_DEFAULT,st_title_line_anchor_col_right_row_3,true,NULL,fullscreen_on,fullscreen_off,1);
    if(SDL_GetWindowFlags(THIS_GAME->window) & SDL_WINDOW_FULLSCREEN)
        st_button_fullscreen->isPressed = true;

    st_text_master = UI_newText(st_panel->menu,LM_getTradById("options_menu_sound_master"),st_title_line_anchor_col_left_row_2, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_text_music = UI_newText(st_panel->menu,LM_getTradById("options_menu_sound_music"),st_title_line_anchor_col_left_row_3, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_text_effects = UI_newText(st_panel->menu,LM_getTradById("options_menu_sound_effects"),st_title_line_anchor_col_left_row_4, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_text_dialogues = UI_newText(st_panel->menu,LM_getTradById("options_menu_sound_dialogues"),st_title_line_anchor_col_left_row_5, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_slider_master = UI_newSlider(st_panel->menu, &master_volume, 25,4,st_title_line_anchor_col_right_row_2,true,NULL);
    st_slider_music = UI_newSlider(st_panel->menu, &music_volume, 25,4,st_title_line_anchor_col_right_row_3,true,NULL);
    st_slider_effects = UI_newSlider(st_panel->menu, &effects_volume, 25,4,st_title_line_anchor_col_right_row_4,true,NULL);
    st_slider_dialogues = UI_newSlider(st_panel->menu, &dialogues_volume, 25,4,st_title_line_anchor_col_right_row_5,true,NULL);

    st_text_language = UI_newText(st_panel->menu,LM_getTradById("options_menu_accessibility_language"),st_title_line_anchor_col_left_row_2, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_arrow_left_lang = UI_newButton(st_panel->menu, NULL, UI_ARROW,st_title_line_anchor_col_right_row_3,true,NULL,fullscreen_on,fullscreen_off,1);
    st_arrow_right_lang = UI_newButton(st_panel->menu, NULL, UI_ARROW,st_title_line_anchor_col_right_row_3,true,NULL,fullscreen_on,fullscreen_off,1);
    UI_flipButton(st_arrow_left_lang); //<- (!)

    st_text_daltonism = UI_newText(st_panel->menu,LM_getTradById("options_menu_accessibility_daltonism"),st_title_line_anchor_col_left_row_3, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_text_screen_shake = UI_newText(st_panel->menu,LM_getTradById("options_menu_accessibility_screen_shake"),st_title_line_anchor_col_left_row_4, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_text_inverse_x_axis = UI_newText(st_panel->menu,LM_getTradById("options_menu_accessibility_inverse_x"),st_title_line_anchor_col_left_row_5, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_text_inverse_y_axis = UI_newText(st_panel->menu,LM_getTradById("options_menu_accessibility_inverse_y"),st_title_line_anchor_col_left_row_6, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    st_text_text_size = UI_newText(st_panel->menu,LM_getTradById("options_menu_accessibility_text_size"),st_title_line_anchor_col_left_row_7, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    onUpdateSettings();    
}
