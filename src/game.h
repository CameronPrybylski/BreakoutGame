#ifndef _GAME_H_
#define _GAME_H_

#include "paddle.h"
#include "entity.h"
#include "glad/glad.h"
#include "source/shaderClass.h"
#include "source/vbo.h"
#include "source/vao.h"
#include "source/ebo.h"
#include <vector>


class Game {

public:

    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int height, int width);
    bool running();
    void handleEvents();
    void handleKeyDown(SDL_Event event);
    void handleKeyUp(SDL_Event event);
    void update();
    void render();
    void cleanup();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<Entity*> objects;

    Shader* shaderProgram;

    Paddle* paddle;

    bool isRunning;
    bool left;
    bool right;
    int screenHeight;
    int screenWidth;

};
#endif