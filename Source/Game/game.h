#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "textureManager.h"
#include "animationManager.h"
#include "projectileManager.h"
#include "../UI/UI_mainMenu.h"
#include "../Maps/mapManager.h"
#include "../List/SmartList.h"
#include "../Language/lang.h"
#include "../SoundEngine/sound-engine.h"
#include "../keyBindings/keyBindings.h"

typedef enum {DEBUG_NULL, DEBUG_HITBOX, DEBUG_PATH, DEBUG_EL} debug;
typedef enum {GS_LoadingMainMenu, GS_MainMenu, GS_LoadingMap, GS_InGame} gameStatus;

typedef struct GameObject GameObject;
typedef enum {GOT_Turret, GOT_Robot, GOT_Projectile, GOT_Effect, GOT_Core, GOT_DEBUG} GameObjectType;

typedef struct
{
    void (*handleEvents)(void);
    void (*update)(void);
    void (*render)(void);
    void (*clean)(void);
    SDL_Window *window;
    SDL_Renderer *renderer;
    textureManager *textureManager;
    animationManager *animationManager;
    projectileManager *projectileManager;
    mapManager *mapManager;
    langManager *languageManager;
    UI_menu *menu;
    SoundEngine *soundEngine;
    float SEMusicWeight;
    list *gameObjects;
    list *keyBindings;
    GameObject *coreObj;
    bool isRunning;
    debug key_debug;
    gameStatus status;
    SDL_Cursor *currentCursor;
    SDL_Cursor *cursorArrow;
    SDL_Cursor *cursorHand;
    void *selection;
    int mouseX;
    int mouseY;
    bool mouseLeftDown;
    int winWidth;
    int winHeight;
    int cameraX;
    int cameraY;
    bool cameraDragging;
    float cameraScale;

/*
    bool waitingForInputKey;
    int keyBindingOrderList;
    keyBinding *keyChosen;
    char *keyChosenToString;
    UI_button *chosenButtonSettings;
*/
} Game;

Game *initGame(const char* title, int width, int height, bool fullscreen);


struct GameObject{
    void (*update)(void *self);
    void (*render)(void *self);
    void (*delete)(void *self);
    bool (*isAlive)(void *self);
    Game *game;
    GameObjectType type;
    void *actor;
};
