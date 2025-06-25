#ifndef _BALL_H_
#define _BALL_H_

#include "entity.h"

class Ball : Entity{

public:
    Ball(float screenWidth, float screenHeight, float radius, float xStart, float yStart, std::string shaderName);
    ~Ball();

    bool checkOutOfBounds(float screenWidth, float screenHeight, float changeX, float changeY);

    void update() override {}
    void update(float changeX, float changeY, float speed);
    void render() override {}
    void setTextureUniform();
    void Draw(const Renderer& renderer, glm::mat4 proj);
    void cleanup() override{}

    VAO* getVAO() const {return vao;}
    VBO* getVBO() const {return vbo;}
    EBO* getEBO() const {return ebo;}
    Texture* getTexture() const {return texture;}
    glm::mat4 getModel() const {return model;}

    float getX(){return x;}
    float getY(){return y;}
    float getXV(){return xv;}
    float getYV(){return yv;}
    void setXV(float xv){this->xv = xv;}
    void setYV(float yv){this->yv = yv;}
    void setXV(){this->xv *= -1;}
    void setYV(){this->yv *= -1;}
    float getRadius(){return radius;}

private:
    float x;
    float y;
    float xDir;
    float yDir;
    float radius;
    float xv;
    float yv;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    VAO* vao;
    VBO* vbo;
    EBO* ebo;
    Texture* texture;
    
    glm::mat4 model;
    std::string shaderName;

};

#endif