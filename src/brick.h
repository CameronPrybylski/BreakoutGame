#ifndef _BRICK_H_
#define _BRICK_H_

#include "entity.h"
#include<vector>

class Brick : Entity{

private:
    std::vector<float> vertices;

    float x;
    float y;
    float width;
    float height;

public:
    Brick(std::vector<float> vertices, float x, float y, float width, float height);
    ~Brick();

    std::vector<float> getVertices(){return vertices;}
    void setVertices(std::vector<float> vertices);

    float getX(){return x;}
    float getY(){return y;}
    float getWidth(){return width;}
    float getHeight(){return height;}

    void update() override {}
    void render() override {}
    void setTextureUniform();
    void Draw(const Renderer& renderer);
    void cleanup() override{}



};

#endif