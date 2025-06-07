#ifndef _PADDLE_H_
#define _PADDLE_H_
#include "entity.h"

class Paddle : Entity {

public:
    Paddle(int screenHeight, int screenWidth, int paddleHeight, int paddleWidth);
    ~Paddle();

    void update() override;
    void render() override;

private:
    int width;
    int height;
    SDL_Rect rect;
};
#endif