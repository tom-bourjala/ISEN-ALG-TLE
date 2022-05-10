#pragma once

#include "turrets.h"
#include "../Game/game.h"
#include "../Game/camera.h"

void renderTurretSelection(Game *game);
void updateTurretSelection(Game *game);
void handleInputTurretSelection(Game *game, SDL_Event *event);