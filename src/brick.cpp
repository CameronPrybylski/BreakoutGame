#include "brick.h"

Brick::Brick(std::vector<float> vertices, float x, float y, float width, float height) : 
vertices(vertices), x(x), y(y), width(width), height(height)
{
    
}

Brick::~Brick()
{
}

void Brick::setVertices(std::vector<float> vertices)
{
    this->vertices = vertices;
}
