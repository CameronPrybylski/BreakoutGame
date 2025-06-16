#include "game.h"
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

        // Optional: set a default OpenGL clear color (black)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        shaderProgram = new Shader("../res/shaders/default.vert", "../res/shaders/default.frag");


        // Vertices coordinates
        std::vector<GLfloat> vertices = {
            -0.2f, -0.85f, 0.0f, 0.0f, //Lower left Second Pair is texure coordinates
            0.2f, -0.85f, 1.0f, 0.0f, // Lower right
            0.2f, -0.8f, 1.0f, 1.0f, //Upper right
            -0.2f, -0.8f, 0.0f, 1.0f // Upper left

        };
        std::vector<GLuint> indices = {
            0, 1, 2, // Right Triangle
            2, 3, 0 // Left Triangle
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        paddle = new Paddle(vertices, indices);

        //texture = new Texture("../res/textures/trollface.png");
        //Default for Bind is slot 0 so setUniform must match with slot so pass in 0
        //texture->Bind();
        shaderProgram->Bind();
        shaderProgram->setUniform1i("u_Texture", 0);

    }
    else {
        isRunning = false;
    }
}

bool Game::running(){
    return this->isRunning;
}

void Game::handleEvents(){
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
}

void Game::handleKeyUp(SDL_Event event){
    SDL_Keycode keyUp = event.key.keysym.sym;
    if(keyUp == SDLK_a){
        left = false;
    }
    if(keyUp == SDLK_d){
        right = false;
    }
}

void Game::update(){
    float changeX = 0.0f;
    if(right){
        changeX = 0.01f;
    }
    if(left){
        changeX = -0.01f;
    }
    paddle->update(changeX);
}

void Game::render(){
    myRenderer.Clear();
    // ... OpenGL draw code ...
    
    // Tell OpenGL which Shader Program we want to use
    //shaderProgram->Bind();
    //shaderProgram->setUniform1i("u_Texture", 0);
    //shaderProgram->setUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    myRenderer.Draw(*paddle->getVAO(), *paddle->getVBO(), *paddle->getEBO(), *shaderProgram, *paddle->getTexture());
    

    SDL_GL_SwapWindow(window);
}

void Game::cleanup(){
    delete shaderProgram;
   // delete texture;
    delete paddle;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}