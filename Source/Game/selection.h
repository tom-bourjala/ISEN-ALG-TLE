#include "game.h"

typedef enum SelectionType {SELECT_NONE, SELECT_MAP, SELECT_TURRET, SELECT_GAMEOBJECT, SELECT_ITEM} SelectionType;

typedef union SelectedObject {
    int mapId;
    GameObject* gameObject;
    // Item* item;
} SelectedObject;


typedef struct Selection{
    SelectionType type;
    SelectedObject selected;
} Selection;