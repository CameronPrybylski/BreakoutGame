#include "game.h"
#include <iostream>

void checkGLError(const char* label) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "[OpenGL Error] (" << label << "): " << std::hex << err << std::endl;
    }
}

int main(int argc, char* argv[]) {
    Game* mainGame = new Game();
    mainGame->init("Breakout", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800);

    int FPS = 60;
    int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;
    /*
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        return 0;
    }
        std::cout << "Subsystems Initialized" << std::endl;

        // Request OpenGL 3.3 Core Profile (or 4.1 on macOS)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // Create window with OpenGL flag
        SDL_Window* window = SDL_CreateWindow("OpenGL Practice", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "Failed to create SDL window!" << std::endl;
            //isRunning = false;
            //return;
        }

        // Create the OpenGL context
        SDL_GLContext glContext = SDL_GL_CreateContext(window);
        if (!glContext) {
            std::cerr << "Failed to create OpenGL context!" << std::endl;
            //isRunning = false;
            //return;
        }

        // Load OpenGL functions using GLAD
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            //isRunning = false;
            //return;
        }

        std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    
    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    unsigned int indices[] {
        0, 1, 2,
        2, 3, 0
    };

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    Shader shaderProgram("../res/shaders/default.vert", "../res/shaders/default.frag");
    unsigned int vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);
    checkGLError("BufferData vbo");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW); 
    checkGLError("BufferData ebo");
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    checkGLError("Vertex Attrib pointer");
    checkGLError("Shader");

    shaderProgram.Activate();
    checkGLError("Shader Activate");

    //Unbind vao,vbo,ebo
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    shaderProgram.setUniform("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);

    bool keep_window_open = true;
    SDL_Event e;
    float r, g, b;
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
    float increment = 0.05f;
    while(keep_window_open) {
        SDL_PollEvent(&e);
        switch (e.type)
        {
            case SDL_QUIT:
                keep_window_open = false;
                break;
            case SDL_KEYDOWN:
                //handleKeyDown(event);
                break;
            case SDL_KEYUP:
                //handleKeyUp(event);
                break;
            default:
                break;
        }
        
        glClear(GL_COLOR_BUFFER_BIT);
        shaderProgram.Activate();
        if(r >= 1.0f){
            increment = -0.05f;
        }else if(r < 0.0f){
            increment = 0.05f;
        }   
        r += increment;
        shaderProgram.setUniform("u_Color", r, g, b, 1.0f);
        glBindVertexArray(vao);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        checkGLError("Draw Triangle");
        SDL_GL_SwapWindow(window);
        SDL_Delay(16);
    }
    shaderProgram.Delete();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    */
    
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
    delete mainGame;

    return 0;
}
