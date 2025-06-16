#ifndef _PADDLE_H_
#define _PADDLE_H_
#include "entity.h"
#include "source/vbo.h"
#include "source/vao.h"
#include "source/ebo.h"
#include "source/renderer.h"
#include "source/texture.h"
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

    bool checkOutOfBounds(float changeX);

    void update(float changeX);
    void update() override {}
    void render() override;
    void cleanup() override;

    VAO* getVAO() const {return vao;}
    VBO* getVBO() const {return vbo;}
    EBO* getEBO() const {return ebo;}
    Texture* getTexture() const {return texture;}

private:
    std::vector<GLfloat> vertices;
    std::vector<GLuint> indices;
    VAO* vao;
    VBO* vbo;
    EBO* ebo;
    Texture* texture;
};
#endif