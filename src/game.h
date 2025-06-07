#ifndef _GAME_H_
#define _GAME_H_

#include "paddle.h"
#include "glad/glad.h"


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

    GLfloat vertices[18];



    GLuint VAO, VBO;

    GLuint shaderProgram;

    Paddle* paddle;

    bool isRunning;
    bool left;
    bool right;
    int screenHeight;
    int screenWidth;

};
#endif