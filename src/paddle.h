#ifndef _PADDLE_H_
#define _PADDLE_H_
#include "entity.h"
#include "source/vbo.h"
#include "source/vao.h"
#include "source/ebo.h"
#include <vector>


class Paddle : Entity {

public:
    Paddle(std::vector<GLfloat> vertices, std::vector<GLuint> indices);
    ~Paddle();

    void bindVAO();
    void linkVBO();
    void bindVBO();
    void bindEBO();

    void unBindVAO();
    void unBindVBO();
    void unBindEBO();

    void update(float changeX);
    void update() override {}
    void render() override;
    void cleanup() override;

private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    VAO* vao;
    VBO* vbo;
    EBO* ebo;
};
#endif