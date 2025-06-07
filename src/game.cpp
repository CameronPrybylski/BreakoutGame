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

        paddle = new Paddle(height, width, 10, 75);
        screenHeight = height;
        screenWidth = width;

        // Optional: set a default OpenGL clear color (black)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        
        // Vertex Shader source code
        const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
        //Fragment Shader source code
        const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
        "}\n\0";

        // Create Vertex Shader Object and get its reference
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // Attach Vertex Shader source to the Vertex Shader Object
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        // Compile the Vertex Shader into machine code
        glCompileShader(vertexShader);

        // Create Fragment Shader Object and get its reference
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        // Attach Fragment Shader source to the Fragment Shader Object
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        // Compile the Vertex Shader into machine code
        glCompileShader(fragmentShader);

        // Create Shader Program Object and get its reference
        shaderProgram = glCreateProgram();
        // Attach the Vertex and Fragment Shaders to the Shader Program
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        // Wrap-up/Link all the shaders together into the Shader Program
        glLinkProgram(shaderProgram);

        // Delete the now useless Vertex and Fragment Shader objects
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);



        // Vertices coordinates
        vertices[0] = -0.2f;
        vertices[1] =  -0.5f;
        vertices[2] = 0.0f;
        vertices[3] = 0.2f;
        vertices[4] = -0.5f;
        vertices[5] = 0.0f;
        vertices[6] = -0.2f;
        vertices[7] =  0.0f;
        vertices[8] = 0.0f;

        vertices[9] = -0.2f;
        vertices[10] =  0.0f;
        vertices[11] = 0.0f;
        vertices[12] = 0.2f;
        vertices[13] =  -0.5f;
        vertices[14] = 0.0f;
        vertices[15] = 0.2;
        vertices[16] = 0.0f;
        vertices[17] = 0.0f;
        /*
        {
            -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
            0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
            0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
        };
        */

        // Create reference containers for the Vartex Array Object and the Vertex Buffer Object
        //GLuint VAO, VBO;

        // Generate the VAO and VBO with only 1 object each
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        // Make the VAO the current Vertex Array Object by binding it
        glBindVertexArray(VAO);

        // Bind the VBO specifying it's a GL_ARRAY_BUFFER
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // Introduce the vertices into the VBO
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Configure the Vertex Attribute so that OpenGL knows how to read the VBO
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        // Enable the Vertex Attribute so that OpenGL knows to use it
        glEnableVertexAttribArray(0);

        // Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
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
    for(int i = 0; i < 18; i += 3){
        vertices[i]+= changeX;
    }
}

void Game::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    // ... OpenGL draw code ...
    // Tell OpenGL which Shader Program we want to use
    glUseProgram(shaderProgram);
    // Bind the VAO so OpenGL knows to use it
    glBindVertexArray(VAO);
    // Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Draw the triangle using the GL_TRIANGLES primitive
    glDrawArrays(GL_TRIANGLES, 0, 6);

    SDL_GL_SwapWindow(window);
}

void Game::cleanup(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}