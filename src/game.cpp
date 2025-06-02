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
        this->cnt = 0;
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
    cnt++;
}

void Game::render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_Rect rect;
    rect.h = 10;
    rect.w = 10;
    rect.y = 20;
    rect.x = cnt;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

}

void Game::cleanup(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}