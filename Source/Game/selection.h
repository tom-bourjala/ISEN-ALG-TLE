#pragma once
#include "game.h"
#include "../Turrets/turrets.h"

typedef enum SelectionType {SELECT_NONE, SELECT_MAP, SELECT_TURRET, SELECT_GAMEOBJECT, SELECT_ITEM} SelectionType;

typedef union SelectedObject {
    int mapId;
    GameObject* gameObject;
    turretSelection *turretSelection;
} SelectedObject;


typedef struct Selection{
    SelectionType type;
    SelectedObject selected;
} Selection;