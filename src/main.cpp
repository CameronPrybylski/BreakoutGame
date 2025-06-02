#include "game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Game* mainGame = new Game();
    mainGame->init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 700);
    
    while(mainGame->running()){

        mainGame->handleEvents();
        mainGame->update();
        mainGame->render();
    }

    mainGame->cleanup();

    return 0;
}
