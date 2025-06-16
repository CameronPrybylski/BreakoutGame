#include "paddle.h"

Paddle::Paddle(std::vector<GLfloat> vertices, std::vector<GLuint> indices) : vertices(vertices), indices(indices) {
    vao = new VAO();
    vbo = new VBO(vertices, false);
    ebo = new EBO(indices);
    texture = new Texture("../res/textures/paddle.png");

    vao->Bind();
    vao->LinkVBO(*vbo, 0);
    ebo->Bind();
    texture->Bind();

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
}

Paddle::~Paddle(){
    delete vao;
    delete vbo;
    delete ebo;
    delete texture;
}

bool Paddle::checkOutOfBounds(float changeX)
{
    if(vertices[0] <= -1.0f && changeX < 0.0f){
        return true;
    }
    if(vertices[4] >= 1.0 && changeX > 0.0f){
        return true;
    }
    return false;
}

void Paddle::update(float changeX){
    if(!checkOutOfBounds(changeX)){
        for(int i = 0; i < vertices.size(); i += 4){
            vertices[i] += changeX;
        }
        vao->Bind();
        vbo->Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    }
}

void Paddle::render(){
    vao->Bind();
    vbo->Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    vao->Unbind();
    vbo->Unbind();
}

void Paddle::cleanup(){
    vao->Delete();
    vbo->Delete();
    ebo->Delete();
}

