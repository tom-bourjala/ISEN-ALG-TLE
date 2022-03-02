#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../List/SmartList.h"
#include <stdbool.h>

#ifndef UISTRUCT_H
#define UISTRUCT_H

typedef struct
{
    list *buttons;
    list *sliders;
    list *texts;
    list *actionAreas;
    list *textureObjects;
    list *anchors;
    list *panels;
    list *panelButtons;
    void *game;
    void (*update)();
    void (*clear)();
    void (*handleEvent)(bool isDown);
    void (*render)();
}UI_menu;

typedef struct
{
    int (*getX)(void *entry);
    int (*getY)(void *entry);
    UI_menu *menu;
}UI_anchor;

typedef struct
{
    SDL_Rect rect;
    UI_anchor *anchor;
    SDL_Texture *texture;
    int nOfFrames;
    int currentFrame;
    bool hidden;
    UI_menu *menu;
}UI_textureObject;

typedef struct
{
    SDL_Rect rect;
    UI_anchor *anchor;
    bool disabled;
    bool isPressed;
    void (*onClick)(void *entry);
    UI_menu *menu;
}UI_actionArea;

typedef enum{UI_TA_LEFT, UI_TA_CENTER, UI_TA_RIGHT} UI_textAlign;
typedef enum{UI_TJ_UP, UI_TJ_CENTER, UI_TJ_DOWN} UI_textJustify;

typedef struct
{
    char **text;
    char *textCache;
    UI_anchor *anchor;
    UI_textAlign textAlign;
    UI_textJustify textJustify;
    TTF_Font *font;
    SDL_Color color;
    SDL_Texture *texture;
    bool hidden;
    UI_menu *menu;
    SDL_Rect rect;
}UI_text;

typedef enum{UI_ARROW, UI_B_BACK, UI_B_BIG, UI_B_MAIN, UI_B_DIAG, UI_B_DEFAULT, UI_B_LONG, UI_CHECK_DEFAULT, UI_CHECK_SMALL, UI_CHECK_ROUND, UI_CHECK_SQUARE} UI_buttonType;

typedef struct
{
    UI_text *text;
    UI_textureObject *textureObject;
    UI_textureObject *hoverTextureObject;
    UI_actionArea *actionArea;
    SDL_Texture *textureIdle;
    SDL_Texture *textureHover;
    SDL_Texture *texturePress;
    SDL_Texture *textureDisabled;
    bool isHidden;
    bool isPressed;
    bool isSticky;
    bool isDisabled;
    float sizeFactor;
    UI_menu *menu;
    UI_anchor *anchor;
    UI_buttonType type;
    void (*onSetOn)(void *entry);
    void (*onSetOff)(void *entry);
}UI_button;

typedef struct
{
    float *value;
    int width;
    float unitWidth;
    float unitHeight;
    float sizeCoef;
    UI_anchor *anchorCL;
    SDL_Texture *textureGrabber;
    SDL_Texture *textureGrabberIdle;
    SDL_Texture *textureGrabberEnabled;
    SDL_Texture *textureEmpty;
    SDL_Texture *textureFull;
    bool hidden;
    bool isPressed;
    bool updateOnRelease;
    void (*onUpdate)(void *entry);
    UI_menu *menu;
}UI_slider;

typedef enum{UI_PT_A,UI_PT_B,UI_PT_DIAG} UI_panelType;

typedef struct
{
    UI_anchor *anchorLT;
    int width;
    int height;
    SDL_Texture *textureIdle;
    SDL_Texture *textureEnabled;
    SDL_Texture *textureDisabled;
    SDL_Texture *textureCurrent;
    bool isDisabled;
    bool isActive;
    bool isHidden;
    UI_menu *menu;
    UI_panelType type;
    int sizeFactor;
}UI_panel;

typedef struct{
    SDL_Texture *textureIdle;
    SDL_Texture *textureEnabled;
    SDL_Texture *textureDisabled;
    SDL_Texture *textureCurrent;
    bool isDisabled;
    bool isActive;
    SDL_Rect rect;
    int orientation;
    int sizeFactor;
}UI_buttonPanel;

#endif