#include "paddle.h"

Paddle::Paddle(std::vector<GLfloat> vertices, std::vector<GLuint> indices) : vertices(vertices), indices(indices) {
    vao = new VAO();
    vbo = new VBO(vertices, false);
    ebo = new EBO(indices);

    vao->Bind();
    vao->LinkVBO(*vbo, 0);
    ebo->Bind();

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
}

Paddle::~Paddle(){
    delete vao;
    delete vbo;
    delete ebo;
}


void Paddle::update(float changeX){
    for(int i = 0; i < vertices.size(); i += 3){
        vertices[i] += changeX;
    }
}

void Paddle::render(){
    vao->Bind();
    vbo->Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Paddle::cleanup(){
    vao->Delete();
    vbo->Delete();
    ebo->Delete();
}

