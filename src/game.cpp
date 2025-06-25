#include "game.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include <iostream>

Game::Game(){

}

Game::~Game(){

}

void Game::init(const char* title, int xpos, int ypos, int height, int width) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystems Initialized" << std::endl;

        // Request OpenGL 3.3 Core Profile (or 4.1 on macOS)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Create window with OpenGL flag
        window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Failed to create SDL window!" << std::endl;
            isRunning = false;
            return;
        }

        // Create the OpenGL context
        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        if (!glContext) {
            std::cerr << "Failed to create OpenGL context!" << std::endl;
            isRunning = false;
            return;
        }

        // Load OpenGL functions using GLAD
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            isRunning = false;
            return;
        }

        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

        // You no longer use SDL_Renderer — use OpenGL draw calls now
        renderer = nullptr;  // optional: explicitly disable SDL renderer
        isRunning = true;

        //paddle = new Paddle();
        screenHeight = height;
        screenWidth = width;

        proj = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
        view = glm::mat4(1.0f);
        model = glm::mat4(1.0f);
        //glm::mat4 model = glm::translate(model, glm::vec3(-100.0f, 0.0f, 0.0f));

        // Optional: set a default OpenGL clear color (black)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        lives = 3;

        ShaderManager::Load("paddleShader", "../res/shaders/paddle.vert", "../res/shaders/paddle.frag");
        ShaderManager::Load("brickShader", "../res/shaders/brick.vert", "../res/shaders/brick.frag");
        ShaderManager::Load("ballShader", "../res/shaders/ball.vert", "../res/shaders/ball.frag");

        //shaderProgram = new Shader("../res/shaders/default.vert", "../res/shaders/default.frag");


        // Vertices coordinates
        std::vector<GLfloat> paddleVertices = {
            275.0f, 30.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,//Lower left Second Pair is texure coordinates
            425.0f, 30.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Lower right
            425.0f, 50.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,//Upper right
            275.0f, 50.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Upper left
        };
        std::vector<GLuint> paddleIndices = {
            0, 1, 2, // Right Triangle
            2, 3, 0 // Left Triangle
        };

        std::vector<Brick> bricks;
        float r, g, b;
        float rgb[3][3] = {
            {1.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 0.0f, 1.0f}
        };
        float width = 100.0f;
        float height = 50.0f;
        for(int i = 0; i < 3; i++){
            float minY = 550.0f + (i * 50.0f);
            for(int j = 0; j < screenWidth / 10; j++){
                float minX = j * 100.0f;
                //float minY = i * 
                std::vector<float> brickVertices = {
                    minX , minY, 0.0f, 0.0f, rgb[i][0], rgb[i][1], rgb[i][2], 1.0f,
                    minX + 100.0f, minY, 1.0f, 0.0f, rgb[i][0], rgb[i][1], rgb[i][2], 1.0f,
                    minX + 100.0f, minY + 50.0f, 1.0f, 1.0f,rgb[i][0], rgb[i][1], rgb[i][2], 1.0f,
                    minX, minY + 50.0f, 0.0f, 1.0f, rgb[i][0], rgb[i][1], rgb[i][2], 1.0f
                };
                Brick brick(brickVertices, minX + width / 2, minY + height / 2, width, height);
                bricks.push_back(brick);
            }
        }
        /*
        std::vector<float> brickVertices = {
            0.0f, 500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f,
            50.0f, 500.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f,
            50.0f, 550.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f,
            0.0f, 550.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f
        };

        Brick brick1(brickVertices);

        std::vector<float> brick2Vertices = {
            500.0f, 500.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f,
            550.0f, 500.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f,
            550.0f, 550.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.5f,
            500.0f, 550.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.5f
        };

        Brick brick2(brick2Vertices);

        std::vector<float> brick3Vertices = {
            250.0f, 500.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f,
            300.0f, 500.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f,
            300.0f, 550.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f,
            250.0f, 550.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f
        };

        Brick brick3(brick3Vertices);
        std::vector<Brick> bricks = {brick1, brick2, brick3};

        */
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        paddle = new Paddle(150.0f, 20.0f, screenWidth, screenHeight, "paddleShader");

        brickManager = new BrickManager(bricks, "brickShader");
        
        ball = new Ball(screenWidth, screenHeight, 10.0f, 400.0f, 60.0f, "ballShader");

        //texture = new Texture("../res/textures/trollface.png");
        //Default for Bind is slot 0 so setUniform must match with slot so pass in 0
        //texture->Bind();
        paddle->setTextureUniform();
        brickManager->setTextureUniform();
        ball->setTextureUniform();
        /*
        shaderProgram = ShaderManager::Get("paddleShader");
        shaderProgram.Bind();
        shaderProgram.setUniform1i("u_Texture", 0);
        mvp = proj * view * model;
        shaderProgram.setUniformMat4f("u_MVP", mvp);
        */

    }
    else {
        isRunning = false;
    }
}

bool Game::running(){
    return this->isRunning;
}

void Game::handleEvents(){
    if(lives < 0){
        isRunning = false;
    }
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        handleKeyDown(event);
        break;
    case SDL_KEYUP:
        handleKeyUp(event);
        break;
    default:
        break;
    }
}

void Game::handleKeyDown(SDL_Event event){
    SDL_Keycode keyPressed = event.key.keysym.sym;
    if(keyPressed == SDLK_a){
        left = true;
    }
    if(keyPressed == SDLK_d){
        right = true;
    }
    if(keyPressed == SDLK_SPACE){
        space = true;
    }
}

void Game::handleKeyUp(SDL_Event event){
    SDL_Keycode keyUp = event.key.keysym.sym;
    if(keyUp == SDLK_a){
        left = false;
    }
    if(keyUp == SDLK_d){
        right = false;
    }
    if(keyUp == SDLK_SPACE){
        space = false;
    }
}

bool Game::checkBallPaddleCollision()
{
    float ballX = ball->getX();
    float ballY = ball->getY();
    float paddleX = paddle->getX();
    float paddleY = paddle->getY();

    float paddleWidth = paddle->getWidth();
    float paddleHeight = paddle->getHeight();
    float ballRadius = ball->getRadius();

    // Calculate AABB bounds for ball
    float ballLeft   = ballX - ballRadius;
    float ballRight  = ballX + ballRadius;
    float ballTop    = ballY + ballRadius;
    float ballBottom = ballY - ballRadius;

    // Calculate AABB bounds for paddle (assuming center position)
    float paddleLeft   = paddleX - paddleWidth / 2.0f;
    float paddleRight  = paddleX + paddleWidth / 2.0f;
    float paddleTop    = paddleY + paddleHeight / 2.0f;
    float paddleBottom = paddleY - paddleHeight / 2.0f;
    return (ballRight >= paddleLeft &&
            ballLeft <= paddleRight &&
            ballTop >= paddleBottom &&
            ballBottom <= paddleTop);

}

bool Game::checkBallBrickCollision(Brick brick)
{
    float ballX = ball->getX();
    float ballY = ball->getY();
    float brickX = brick.getX();
    float brickY = brick.getY();

    float ballRadius = ball->getRadius();
    float brickWidth = brick.getWidth();
    float brickHeight = brick.getHeight();

    // Calculate AABB bounds for ball
    float ballLeft   = ballX - ballRadius;
    float ballRight  = ballX + ballRadius;
    float ballTop    = ballY + ballRadius;
    float ballBottom = ballY - ballRadius;

    // Calculate AABB bounds for brick
    float brickLeft  = brickX - brickWidth / 2;
    float brickRight = brickX + brickWidth / 2;
    float brickTop = brickY + brickHeight / 2;
    float brickBottom = brickY - brickHeight / 2;
    return (ballLeft <= brickRight &&
            ballRight >= brickLeft &&
            ballTop >= brickBottom &&
            ballBottom <= brickTop);
}

void Game::update(){
    float changeX = 0.0f;
    if(right){
        changeX = screenWidth * 0.01f;
    }
    if(left){
        changeX = screenWidth * -0.01f;
    }
    if(space && ball->getXV() == 0.0f && ball->getYV() == 0.0f){
        ball->setXV(1.0f);
        ball->setYV(1.0f);
        lives--;
        if(lives < 0){
            isRunning = false;
        }
    }
    std::vector<Brick> bricks = brickManager->getBricks();
    for(int i = 0; i < bricks.size(); i++)
    {
        if(checkBallBrickCollision(bricks[i]))
        {
            ball->setYV();
            brickManager->removeBrick(i);
            break;
        }
    }
    paddle->update(changeX, screenWidth);
    bool collision = checkBallPaddleCollision();
    if(collision)
    {
        ball->setYV();
    }
    ball->update(3.0f, 3.0f, 1.0f);
    brickManager->update();
    //model = paddle->getModel();
    //model = glm::translate(model, glm::vec3(changeX, 0.0f, 0.0f));
}

void Game::render(){
    myRenderer.Clear();
    // ... OpenGL draw code ...
    
    // Tell OpenGL which Shader Program we want to use
    //shaderProgram->Bind();
    //shaderProgram->setUniform1i("u_Texture", 0);
    //shaderProgram->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    //mvp = proj * view * model;
    //shaderProgram.setUniformMat4f("u_MVP", mvp);
    //myRenderer.Draw(*paddle->getVAO(), *paddle->getVBO(), *paddle->getEBO(), shaderProgram, *paddle->getTexture());
    paddle->Draw(myRenderer, proj);
    brickManager->Draw(myRenderer, proj);
    ball->Draw(myRenderer, proj);

    SDL_GL_SwapWindow(window);
}

void Game::cleanup(){
    //delete shaderProgram;
    ShaderManager::Clear();
   // delete texture;
    delete paddle;
    delete brickManager;
    delete ball;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}