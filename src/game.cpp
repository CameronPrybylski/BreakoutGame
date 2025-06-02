#include "game.h"
#include <iostream>

Game::Game(){

}

Game::~Game(){

}

void Game::init(const char* title, int xpos, int ypos, int height, int width){
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystems Initialized" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        this->isRunning = true;
        
        this->screenHeight = height;
        this->screenWidth = width;
    }
    else{
        this->isRunning = false;
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
        break;
    case SDL_KEYUP:
        break;
    default:
        break;
    }
}

void Game::update(){

}

void Game::render(){
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
}

void Game::cleanup(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}