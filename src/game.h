#ifndef _GAME_H_
#define _GAME_H_

#include "paddle.h"
#include "ball.h"
#include "brickmanager.h"
#include "entity.h"
#include "glad/glad.h"
#include "../res/shaders/shaderClass.h"
#include "../res/shaders/shaderManager.h"
#include "source/vbo.h"
#include "source/vao.h"
#include "source/ebo.h"
#include "source/renderer.h"
#include "source/texture.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
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
    bool checkBallPaddleCollision();
    bool checkBallBrickCollision(Brick brick);
    void update();
    void render();
    void cleanup();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::vector<Entity*> objects;

    Shader shaderProgram;

    Paddle* paddle;
    BrickManager* brickManager;
    Ball* ball;

    Renderer myRenderer;

    Texture* texture;

    bool isRunning;
    bool left;
    bool right;
    bool space;
    int lives;
    int screenHeight;
    int screenWidth;

    glm::mat4 proj;
    glm::mat4 view;
    glm::mat4 model;
    glm::mat4 mvp;

};
#endif