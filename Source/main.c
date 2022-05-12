#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./Game/game.h"
#include "./List/SmartList.h"
#include "./Turrets/turrets.h"
#include "./Robots/robots.h"

#define MAIN_C


Game *game = NULL;

int main(int argc, const char * argv[]) {
    int FPS = 60;
    int frameDelta = 1000 / FPS;
    game = initGame("The Last Engineer", 1920, 1080, false);
    // game->mapManager->loadMap("debug", 1900, 1000);
    
    // list *starts = game->mapManager->currentMap->starts;
    Uint32 frameStart;
    int frameTime;
    // for(int x = 0; x < 5; x++){
    //     appendInList(game->gameObjects, newGameObject_Robot(game, "debug.robot", getDataAtIndex(*starts, 0), 0));
    //     appendInList(game->gameObjects, newGameObject_Robot(game, "debug.robot", getDataAtIndex(*starts, 0), 1));
    //     appendInList(game->gameObjects, newGameObject_Robot(game, "debug.robot", getDataAtIndex(*starts, 1), 0));
    //     appendInList(game->gameObjects, newGameObject_Robot(game, "debug.robot", getDataAtIndex(*starts, 1), 1));
    // }
    
    while(game->isRunning){

        frameStart = SDL_GetTicks();
        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelta > frameTime) SDL_Delay(frameDelta - frameTime);
        // else if(frameTime - frameDelta > 30) printf("\033[1;33mPerformances Issues : %d ms frame processing time excess.\033[0m\n", frameTime - frameDelta);
    }
    game->clean();
    return 0;
}
