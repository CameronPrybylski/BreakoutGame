#include "paddle.h"

Paddle::Paddle(int screenHeight, int screenWidth, int paddleHeight, int paddleWidth) : height(paddleHeight), width(paddleWidth) {
    rect.h = paddleHeight;
    rect.w = paddleWidth;

}

Paddle::~Paddle(){

}

void Paddle::update(){

}

void Paddle::render(){

}
