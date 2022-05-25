/* Key rebinding lib for TLE. */
#pragma once

#include "../List/SmartList.h"
#include "../Game/game.h"
#include <string.h>
#include <SDL2/SDL.h>

//game input enumeration support
typedef int gameInput;

//key rebinding item
typedef struct
{
    SDL_Keycode key;
    gameInput input;
} keyBinding;

typedef struct
{
    SDL_Keycode code;
    SDL_Texture *texture;
}keyTexture;

// "KB" stands for "Key Binding"

/* @brief: Initializes the key rebinding library.
 * @return: List pointer to smartList item.
 */
list *KB_init(void *game);

/* @brief: free the key rebinding library. Removes all items from the list.
 */
void KB_free();

/* @brief: Adds a key binding to the list. Ignore if binding already exists.
 * @param: key SDL_Keycode to bind.
 * @param: input gameInput to bind.
 */
void KB_add(SDL_Keycode key, gameInput input);

/* @brief: Removes a key binding from the list. Ignore if binding does not exist.
 * @param: kb keyBinding to remove.
 */
void KB_removeKeyBinding(keyBinding *kb);

/* @brief: get a list of inputs linked to a key.
 * @param: key SDL_Keycode to get inputs for.
 * @return: List of inputs. NULL if no inputs are linked to key.
 */
list *KB_getInputs(SDL_Keycode key);

/* @brief: get a list of keys linked to an input.
 * @param: input gameInput to get keys for.
 * @return: List of keys. NULL if no keys are linked to input.
 */
list *KB_getKeys(gameInput input);

/* @brief: get a key binding from the list.
 * @param: key SDL_Keycode to get binding for.
 * @param: input gameInput to get binding for.
 * @return: Pointer to keyBinding. NULL if binding does not exist.
 */
keyBinding *KB_getKeyBinding(SDL_Keycode key, gameInput input);

/*
 * @brief: comparator function for the list
 * @param: void pointer representing a keyBinding
 * @param: void pointer representing a keyBinding
 * @return: int. 0 if true, else -1;
 */
int Comparator(void *needle, void *data);

void printed();
void printList(list *r);

void KB_getInput(void (*callback)(SDL_Keycode code,void *data),void *data);
void KB_handleKeyCode(SDL_Keycode code, Game *game);
list *KB_getKCTA();


typedef enum{NONE,GA_UP,GA_DOWN,GA_LEFT,GA_RIGHT,GA_ZOOMIN,GA_ZOOMOUT,GA_TURRET1,GA_TURRET2,GA_TURRET3,GA_PAUSE,GA_SELL,GA_UPGRADE}GA_type;
int getCountInputOrder(int count_input);