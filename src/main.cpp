#include "game.h"
#include <iostream>

int main(int argc, char* argv[]) {
    Game* mainGame = new Game();
    mainGame->init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 700);

    int FPS = 60;
    int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    
    while(mainGame->running()){

        frameStart = SDL_GetTicks();

        mainGame->handleEvents();
        mainGame->update();
        mainGame->render();

        frameTime = SDL_GetTicks() - frameStart;
        if(frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

    }

    mainGame->cleanup();

    return 0;
}
