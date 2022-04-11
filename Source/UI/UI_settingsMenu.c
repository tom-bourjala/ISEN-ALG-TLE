#include "UI_settingsMenu.h"
#include "../Game/game.h"
#include <stdbool.h>

static Game *THIS_GAME = NULL;
static UI_menu *backStateMenu = NULL;

int getLT_x(void *none){return 200;}
int getLT_y(void *none){return 100;}

UI_panel *settings_panel = NULL;
static UI_panelButton *settings_button_general = NULL;
static UI_button *settings_button_back = NULL;
static UI_panelButton *settings_button_resolution = NULL;
static UI_text *settings_text_resolution = NULL;
static UI_text *settings_text_fullscreen = NULL;
static UI_button *settings_button_fullscreen = NULL;
static float screen_size = 0.5;
static float master_volume = 0.5;
static float music_volume = 0.5;
static float effects_volume = 0.5;
static float dialogues_volume = 0.5;

static UI_slider *settings_slider_resolution = NULL;
static UI_slider *settings_slider_master = NULL;
static UI_slider *settings_slider_music = NULL;
static UI_slider *settings_slider_effects = NULL;
static UI_slider *settings_slider_dialogues = NULL;

static UI_panelButton *settings_button_audio = NULL;
static UI_text *settings_text_master = NULL;
static UI_text *settings_text_music = NULL;
static UI_text *settings_text_effects = NULL;
static UI_text *settings_text_dialogues = NULL;

static UI_text *settings_text_general_title = NULL;
static UI_text *settings_text_display_title = NULL;
static UI_text *settings_text_audio_title = NULL;
static UI_text *settings_text_commands_title = NULL;
static UI_text *settings_text_accessibility_title = NULL;

static UI_panelButton *settings_button_commands = NULL;

static UI_panelButton *settings_button_accessibility = NULL;
static UI_text *settings_text_language = NULL;
static UI_text *settings_text_daltonism = NULL;
static UI_text *settings_text_screen_shake = NULL;
static UI_text *settings_text_inverse_x_axis = NULL;
static UI_text *settings_text_inverse_y_axis = NULL;
static UI_text *settings_text_text_size = NULL;

static UI_button *settings_arrow_left_lang = NULL;
static UI_button *settings_arrow_right_lang = NULL;
static UI_button *settings_text_resolution_800_600 = NULL;
static UI_button *settings_text_resolution_1200_800 = NULL;
static UI_button *settings_text_resolution_1600_1000 = NULL;
static UI_button *settings_text_resolution_1920_1080 = NULL;

static char **(*LM_getTradById)(char *string) = NULL;

int getPannelMiddle_x(void *none){return THIS_GAME->winWidth/2;}
int getPannelMiddle_y(void *none){return THIS_GAME->winHeight/2;}

int back_button_anchor_x(void *non){return getPannelMiddle_x(NULL)+455;}
int back_button_anchor_y(void *non){return getPannelMiddle_y(NULL)+350;}

int col_left_x(void *none){return settings_panel->width/4+getLT_x(NULL);}
int col_right_x(void *none){return 2*settings_panel->width/3+getLT_x(NULL);}

int settings_title_x(void *none){return getPannelMiddle_x(NULL)-550;}
int settings_title_y(void *none){return getPannelMiddle_y(NULL)-230;}

int settings_text_row_1(void *none){return getPannelMiddle_y(NULL)-200;}
int settings_text_row_2(void *none){return getPannelMiddle_y(NULL)-140;}
int settings_text_row_3(void *none){return getPannelMiddle_y(NULL)-80;}
int settings_text_row_4(void *none){return getPannelMiddle_y(NULL)-20;}
int settings_text_row_5(void *none){return getPannelMiddle_y(NULL)+40;}
int settings_text_row_6(void *none){return getPannelMiddle_y(NULL)+100;}
int settings_text_row_7(void *none){return getPannelMiddle_y(NULL)+160;}

typedef enum{US,FR,CA} LANGUAGES;
static int lang_choice = US;

void showGeneral(void)
{   settings_slider_master->hidden = true;
    settings_slider_music->hidden = true;
    settings_slider_effects->hidden = true;
    settings_slider_dialogues->hidden = true;
    settings_slider_resolution->hidden = true;
    settings_button_fullscreen->hidden = true;
    settings_text_general_title->hidden = false;
    settings_text_display_title->hidden = true;
    settings_text_audio_title->hidden = true;
    settings_text_commands_title->hidden = true;
    settings_text_accessibility_title->hidden = true;
    settings_text_resolution->hidden = true;
    settings_text_fullscreen->hidden = true;
    settings_text_master->hidden = true;
    settings_text_music->hidden = true;
    settings_text_effects->hidden = true;
    settings_text_dialogues->hidden = true;
    settings_text_language->hidden = true;
    settings_text_daltonism->hidden = true;
    settings_text_screen_shake->hidden = true;
    settings_text_inverse_x_axis->hidden = true;
    settings_text_inverse_y_axis->hidden = true;
    settings_text_text_size->hidden = true;
}

void showResolution(void)
{
    settings_slider_master->hidden = true;
    settings_slider_music->hidden = true;
    settings_slider_effects->hidden = true;
    settings_slider_dialogues->hidden = true;
    settings_slider_resolution->hidden = false;
    settings_button_fullscreen->hidden = false;
    settings_text_general_title->hidden = true;
    settings_text_display_title->hidden = false;
    settings_text_audio_title->hidden = true;
    settings_text_commands_title->hidden = true;
    settings_text_accessibility_title->hidden = true;
    settings_text_resolution->hidden = false;
    settings_text_fullscreen->hidden = false;
    settings_text_master->hidden = true;
    settings_text_music->hidden = true;
    settings_text_effects->hidden = true;
    settings_text_dialogues->hidden = true;
    settings_text_language->hidden = true;
    settings_text_daltonism->hidden = true;
    settings_text_screen_shake->hidden = true;
    settings_text_inverse_x_axis->hidden = true;
    settings_text_inverse_y_axis->hidden = true;
    settings_text_text_size->hidden = true;
}

void showAudio(void)
{
    settings_slider_master->hidden = false;
    settings_slider_music->hidden = false;
    settings_slider_effects->hidden = false;
    settings_slider_dialogues->hidden = false;
    settings_slider_resolution->hidden = true;
    settings_button_fullscreen->hidden = true;
    settings_text_general_title->hidden = true;
    settings_text_display_title->hidden = true;
    settings_text_audio_title->hidden = false;
    settings_text_commands_title->hidden = true;
    settings_text_accessibility_title->hidden = true;
    settings_text_resolution->hidden = true;
    settings_text_fullscreen->hidden = true;
    settings_text_master->hidden = false;
    settings_text_music->hidden = false;
    settings_text_effects->hidden = false;
    settings_text_dialogues->hidden = false;
    settings_text_language->hidden = true;
    settings_text_daltonism->hidden = true;
    settings_text_screen_shake->hidden = true;
    settings_text_inverse_x_axis->hidden = true;
    settings_text_inverse_y_axis->hidden = true;
    settings_text_text_size->hidden = true;
}

void showCommands(void)
{
    settings_slider_master->hidden = true;
    settings_slider_music->hidden = true;
    settings_slider_effects->hidden = true;
    settings_slider_dialogues->hidden = true;
    settings_slider_resolution->hidden = true;
    settings_button_fullscreen->hidden = true;
    settings_text_general_title->hidden = true;
    settings_text_display_title->hidden = true;
    settings_text_audio_title->hidden = true;
    settings_text_commands_title->hidden = false;
    settings_text_accessibility_title->hidden = true;
    settings_text_resolution->hidden = true;
    settings_text_fullscreen->hidden = true;
    settings_text_master->hidden = true;
    settings_text_music->hidden = true;
    settings_text_effects->hidden = true;
    settings_text_dialogues->hidden = true;
    settings_text_language->hidden = true;
    settings_text_daltonism->hidden = true;
    settings_text_screen_shake->hidden = true;
    settings_text_inverse_x_axis->hidden = true;
    settings_text_inverse_y_axis->hidden = true;
    settings_text_text_size->hidden = true;
}

void showAccessibility(void)
{
    settings_slider_master->hidden = true;
    settings_slider_music->hidden = true;
    settings_slider_effects->hidden = true;
    settings_slider_dialogues->hidden = true;
    settings_slider_resolution->hidden = true;
    settings_button_fullscreen->hidden = true;
    settings_text_general_title->hidden = true;
    settings_text_display_title->hidden = true;
    settings_text_audio_title->hidden = true;
    settings_text_commands_title->hidden = true;
    settings_text_accessibility_title->hidden = false;
    settings_text_resolution->hidden = true;
    settings_text_fullscreen->hidden = true;
    settings_text_master->hidden = true;
    settings_text_music->hidden = true;
    settings_text_effects->hidden = true;
    settings_text_dialogues->hidden = true;
    settings_text_language->hidden = false;
    settings_text_daltonism->hidden = false;
    settings_text_screen_shake->hidden = false;
    settings_text_inverse_x_axis->hidden = false;
    settings_text_inverse_y_axis->hidden = false;
    settings_text_text_size->hidden = false;
}

void onUpdateSettings(){
    //printf("%d x %d\n",THIS_GAME->mouseX,THIS_GAME->mouseY);
    settings_panel->width = THIS_GAME->winWidth - (getLT_x(NULL)*2);
    settings_panel->height = THIS_GAME->winHeight - (getLT_y(NULL)*2);

    /*int max_x,max_y;
    SDL_GetWindowMaximumSize(THIS_GAME->window,&max_x,&max_y);
    SDL_SetWindowSize(THIS_GAME->window,800+(abs(max_x-800))*(*settings_slider_resolution->value),600+(abs(max_x-600))*(*settings_slider_resolution->value));
    */

    if(settings_button_general->isActive == true)
    {
        showGeneral();
    }
    if(settings_button_audio->isActive == true)
    {
        showAudio();
    }
    if(settings_button_resolution->isActive == true)
    {
        showResolution();
    }
    if(settings_button_commands->isActive == true)
    {
        showCommands();
    }
    if(settings_button_accessibility->isActive == true)
    {
        showAccessibility();
    }
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
    settings_button_general->isActive = (self == settings_button_general);
    settings_button_audio->isActive = (self == settings_button_audio);
    settings_button_resolution->isActive = (self == settings_button_resolution);
    settings_button_commands->isActive = (self == settings_button_commands);
    settings_button_accessibility->isActive = (self == settings_button_accessibility);
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
    settings_panel = UI_newPanel(game->menu, 0, 0, A_LC, 2, UI_PT_A);
    
    settings_panel->isActive = true;
    settings_button_general = UI_newButtonPanel(settings_panel, LM_getTradById("menu_settings_general"), (SDL_Rect){100,0,200,50}, 0,onMenuSwitch);
    settings_button_general->isActive = true;
    settings_button_resolution = UI_newButtonPanel(settings_panel, LM_getTradById("menu_settings_display"), (SDL_Rect){300,0,200,50}, 0,onMenuSwitch);
    settings_button_audio = UI_newButtonPanel(settings_panel, LM_getTradById("menu_settings_audio"), (SDL_Rect){500,0,200,50}, 0,onMenuSwitch);
    settings_button_commands = UI_newButtonPanel(settings_panel, LM_getTradById("menu_settings_commands"), (SDL_Rect){700,0,200,50}, 0,onMenuSwitch);
    settings_button_accessibility = UI_newButtonPanel(settings_panel, LM_getTradById("menu_settings_accessibility"), (SDL_Rect){900,0,200,50}, 0,onMenuSwitch);
    settings_button_back = UI_newButton(game->menu, LM_getTradById("menu_settings_back"), UI_B_BACK,anchor_back_button,false,onClear,NULL,NULL,1);

    SDL_Color white = {255,255,255,255};
    UI_anchor *settings_title_anchor = UI_newAnchor(game->menu, settings_title_x, settings_title_y);
    settings_text_general_title = UI_newText(game->menu,LM_getTradById("menu_settings_general"),settings_title_anchor, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 60);
    settings_text_display_title = UI_newText(game->menu,LM_getTradById("menu_settings_display"),settings_title_anchor, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 60);
    settings_text_audio_title = UI_newText(game->menu,LM_getTradById("menu_settings_audio"),settings_title_anchor, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 60);
    settings_text_commands_title = UI_newText(game->menu,LM_getTradById("menu_settings_commands"),settings_title_anchor, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 60);
    settings_text_accessibility_title = UI_newText(game->menu,LM_getTradById("menu_settings_accessibility"),settings_title_anchor, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 60);

    UI_anchor *settings_title_line_anchor_col_left_row_1 = UI_newAnchor(game->menu, col_left_x, settings_text_row_1);
    UI_anchor *settings_title_line_anchor_col_left_row_2 = UI_newAnchor(game->menu, col_left_x, settings_text_row_2);
    UI_anchor *settings_title_line_anchor_col_left_row_3 = UI_newAnchor(game->menu, col_left_x, settings_text_row_3);
    UI_anchor *settings_title_line_anchor_col_left_row_4 = UI_newAnchor(game->menu, col_left_x, settings_text_row_4);
    UI_anchor *settings_title_line_anchor_col_left_row_5 = UI_newAnchor(game->menu, col_left_x, settings_text_row_5);
    UI_anchor *settings_title_line_anchor_col_left_row_6 = UI_newAnchor(game->menu, col_left_x, settings_text_row_6);
    UI_anchor *settings_title_line_anchor_col_left_row_7 = UI_newAnchor(game->menu, col_left_x, settings_text_row_7);
    UI_anchor *settings_title_line_anchor_col_right_row_1 = UI_newAnchor(game->menu, col_right_x, settings_text_row_1);
    UI_anchor *settings_title_line_anchor_col_right_row_2 = UI_newAnchor(game->menu, col_right_x, settings_text_row_2);
    UI_anchor *settings_title_line_anchor_col_right_row_3 = UI_newAnchor(game->menu, col_right_x, settings_text_row_3);
    UI_anchor *settings_title_line_anchor_col_right_row_4 = UI_newAnchor(game->menu, col_right_x, settings_text_row_4);
    UI_anchor *settings_title_line_anchor_col_right_row_5 = UI_newAnchor(game->menu, col_right_x, settings_text_row_5);
    UI_anchor *settings_title_line_anchor_col_right_row_6 = UI_newAnchor(game->menu, col_right_x, settings_text_row_6);
    UI_anchor *settings_title_line_anchor_col_right_row_7 = UI_newAnchor(game->menu, col_right_x, settings_text_row_7);

    settings_text_resolution = UI_newText(settings_panel->menu,LM_getTradById("options_menu_video_resolution"),settings_title_line_anchor_col_left_row_2, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_slider_resolution = UI_newSlider(settings_panel->menu, &screen_size, 25,4,settings_title_line_anchor_col_right_row_2,true,NULL);
    // a implementer

    settings_text_fullscreen = UI_newText(settings_panel->menu,LM_getTradById("options_menu_video_fullscreen"),settings_title_line_anchor_col_left_row_3, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_button_fullscreen = UI_newButton(settings_panel->menu, NULL, UI_CHECK_DEFAULT,settings_title_line_anchor_col_right_row_3,true,NULL,fullscreen_on,fullscreen_off,1);
    if(SDL_GetWindowFlags(THIS_GAME->window) & SDL_WINDOW_FULLSCREEN)
    {
        settings_button_fullscreen->isPressed = true;
    }

    settings_text_master = UI_newText(settings_panel->menu,LM_getTradById("options_menu_sound_master"),settings_title_line_anchor_col_left_row_2, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_text_music = UI_newText(settings_panel->menu,LM_getTradById("options_menu_sound_music"),settings_title_line_anchor_col_left_row_3, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_text_effects = UI_newText(settings_panel->menu,LM_getTradById("options_menu_sound_effects"),settings_title_line_anchor_col_left_row_4, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_text_dialogues = UI_newText(settings_panel->menu,LM_getTradById("options_menu_sound_dialogues"),settings_title_line_anchor_col_left_row_5, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_slider_master = UI_newSlider(settings_panel->menu, &master_volume, 25,4,settings_title_line_anchor_col_right_row_2,true,NULL);
    settings_slider_music = UI_newSlider(settings_panel->menu, &music_volume, 25,4,settings_title_line_anchor_col_right_row_3,true,NULL);
    settings_slider_effects = UI_newSlider(settings_panel->menu, &effects_volume, 25,4,settings_title_line_anchor_col_right_row_4,true,NULL);
    settings_slider_dialogues = UI_newSlider(settings_panel->menu, &dialogues_volume, 25,4,settings_title_line_anchor_col_right_row_5,true,NULL);

    settings_text_language = UI_newText(settings_panel->menu,LM_getTradById("options_menu_accessibility_language"),settings_title_line_anchor_col_left_row_2, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_arrow_left_lang = UI_newButton(settings_panel->menu, NULL, UI_ARROW,settings_title_line_anchor_col_right_row_3,true,NULL,fullscreen_on,fullscreen_off,1);
    settings_arrow_right_lang = UI_newButton(settings_panel->menu, NULL, UI_ARROW,settings_title_line_anchor_col_right_row_3,true,NULL,fullscreen_on,fullscreen_off,1);
    UI_flipButton(settings_arrow_left_lang); //<- (!)
    settings_text_resolution_800_600 = UI_newButton(settings_panel->menu,LM_getTradById("options_menu_video_800_600"),UI_B_DEFAULT, settings_title_line_anchor_col_right_row_3, false,NULL,NULL,NULL,1);
    settings_text_resolution_1200_800 = UI_newButton(settings_panel->menu,LM_getTradById("options_menu_video_1200_800"),UI_B_DEFAULT, settings_title_line_anchor_col_right_row_3, false,NULL,NULL,NULL,1);
    settings_text_resolution_1600_1000 = UI_newButton(settings_panel->menu,LM_getTradById("options_menu_video_1600_1000"),UI_B_DEFAULT, settings_title_line_anchor_col_right_row_3, false,NULL,NULL,NULL,1);
    settings_text_resolution_1920_1080 = UI_newButton(settings_panel->menu,LM_getTradById("options_menu_video_1920_1080"),UI_B_DEFAULT, settings_title_line_anchor_col_right_row_3, false,NULL,NULL,NULL,1);
    settings_text_resolution_800_600->hidden = true;
    settings_text_resolution_1200_800->hidden = true;
    settings_text_resolution_1600_1000->hidden = true;
    settings_text_resolution_1920_1080->hidden = true;

    settings_text_daltonism = UI_newText(settings_panel->menu,LM_getTradById("options_menu_accessibility_daltonism"),settings_title_line_anchor_col_left_row_3, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_text_screen_shake = UI_newText(settings_panel->menu,LM_getTradById("options_menu_accessibility_screen_shake"),settings_title_line_anchor_col_left_row_4, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_text_inverse_x_axis = UI_newText(settings_panel->menu,LM_getTradById("options_menu_accessibility_inverse_x"),settings_title_line_anchor_col_left_row_5, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_text_inverse_y_axis = UI_newText(settings_panel->menu,LM_getTradById("options_menu_accessibility_inverse_y"),settings_title_line_anchor_col_left_row_6, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    settings_text_text_size = UI_newText(settings_panel->menu,LM_getTradById("options_menu_accessibility_text_size"),settings_title_line_anchor_col_left_row_7, UI_TA_LEFT, UI_TJ_CENTER,white, "./assets/fonts/RulerGold.ttf", 30);
    onUpdateSettings();    
}
