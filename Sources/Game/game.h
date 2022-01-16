#include <SDL2/SDL.h>
#include <stdio.h>
#include <stlib.h>
#include <time.h>

typedef struct
{
    void (*handleEvents)(void);
    void (*update)(void);
    void (*render)(void);
    void (*clean)(void);
    bool (*isRunning)(void);
    SDL_Window *window;
    SDL_Renderer *renderer;
} Game;

Game *initGame(const char* title, int width, int height, bool fullscreen);

typedef struct
{
    void (*update)(GameObject *self);
    void (*render)(GameObject *self);
    void (*delete)(GameObject *self);
    bool (*isAlive)(GameObject *self);
    SDL_Window *window;
    void *actor;
} GameObject;

typedef enum{BALLISTIC, PLASMA, EXPLOSIVE} weaponType;

typedef struct{
    int speed;
    int damage;
    weaponType type;
    GameObject *parent;
} projectile;

typedef struct{
    int damage;
    weaponType type;
    GameObject *parent;
    GameObject *target;
} hit;

typedef struct
{
    int x;
    int y;
} point;
