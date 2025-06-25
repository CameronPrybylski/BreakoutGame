#ifndef _PADDLE_H_
#define _PADDLE_H_
#include "entity.h"
#include "source/vbo.h"
#include "source/vao.h"
#include "source/ebo.h"
#include "source/renderer.h"
#include "source/texture.h"

#include <vector>
#include <string>


class Paddle : Entity {

public:
    Paddle(float width, float height, float screenWidth, float screenHeight, std::string shaderName);
    ~Paddle();

    void bindVAO();
    void linkVBO();
    void bindVBO();
    void bindEBO();

    void unBindVAO();
    void unBindVBO();
    void unBindEBO();

    bool checkOutOfBounds(float changeX, float screenWidth);

    void update(float changeX, float screenWidth);
    void update() override {}
    void render() override;
    void setTextureUniform();
    void Draw(const Renderer& renderer, glm::mat4 proj);
    void cleanup() override;

    VAO* getVAO() const {return vao;}
    VBO* getVBO() const {return vbo;}
    EBO* getEBO() const {return ebo;}
    Texture* getTexture() const {return texture;}
    glm::mat4 getModel() const {return model;}

    float getX(){return x;}
    float getY(){return y;}
    float getWidth(){return width;}
    float getHeight(){return height;}

private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    VAO* vao;
    VBO* vbo;
    EBO* ebo;
    Texture* texture;
    float width;
    float height;
    float x;
    float y;
    glm::mat4 model;
    std::string shaderName;
};
#endif