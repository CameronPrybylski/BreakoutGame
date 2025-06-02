#ifndef _GAME_H_
#define _GAME_H_

#include "SDL.h"

class Game {

public:

    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int height, int width);
    bool running();
    void handleEvents();
    void update();
    void render();
    void cleanup();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isRunning;
    int screenHeight;
    int screenWidth;

};
#endif