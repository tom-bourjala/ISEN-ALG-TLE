#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./Game/game.h"

Game *game = NULL;

int main(int argc, const char * argv[]){
    game = initGame("The Last Engineer", 800, 600, false);
    while(game->isRunning){
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    return 0;
}
