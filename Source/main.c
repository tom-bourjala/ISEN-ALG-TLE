#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./Game/game.h"
#include "./List/SmartList.h"


Game *game = NULL;

int main(int argc, const char * argv[]) {
    int FPS = 60;
    int frameDelta = 1000 / FPS;
    game = initGame("The Last Engineer", 1300, 900, false);

    Uint32 frameStart;
    int frameTime;

    while(game->isRunning){
        frameStart = SDL_GetTicks();
        
        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelta > frameTime) SDL_Delay(frameDelta - frameTime);
        else if(frameTime - frameDelta > 30) printf("\033[1;33mPerformances Issues : %d ms frame processing time excess.\033[0m\n", frameTime - frameDelta);
    }
    game->clean();
    return 0;
}
