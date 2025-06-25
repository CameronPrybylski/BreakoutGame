#include "paddle.h"
#include "../res/shaders/shaderManager.h"
#include "brickmanager.h"

Paddle::Paddle(float width, float height, float screenWidth, float screenHeight, std::string shaderName) : 
width(width), height(height), shaderName(shaderName)
{
    float halfWidth = width / 2;
    float halfHeight = height / 2;
    // Vertices coordinates
    std::vector<float> vertices = {
        -halfWidth, -halfHeight, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,//Lower left Second Pair is texure coordinates
        halfWidth, -halfHeight, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Lower right
        halfWidth, halfHeight, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,//Upper right
        -halfWidth, halfHeight, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Upper left
    };
    std::vector<unsigned int> indices = {
        0, 1, 2, // Right Triangle
        2, 3, 0 // Left Triangle
    };
    vao = new VAO();
    vbo = new VBO(vertices, false);
    ebo = new EBO(indices);
    texture = new Texture("../res/textures/paddle.png");
    model = glm::mat4(1.0f);
    x = 400.0f;
    y = 40.0f;


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

bool Paddle::checkOutOfBounds(float changeX, float screenWidth)
{
    float newX = x + changeX;
    float halfWidth = width / 2;
    //float halfScreenWidth = screenWidth / 2;
    if(newX - width / 2 < 0.0f || newX + width / 2 > screenWidth){
        return true;
    }
    return false;
}

void Paddle::update(float changeX, float screenWidth){
    if(!checkOutOfBounds(changeX, screenWidth)){
        x += changeX;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
        /*
        for(int i = 0; i < vertices.size(); i += 4){
            vertices[i] += changeX;
        }
        vao->Bind();
        vbo->Bind();
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
        */
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

void Paddle::setTextureUniform()
{
    Shader& paddleShader = ShaderManager::Get(shaderName);
    paddleShader.Bind();
    paddleShader.setUniform1i("u_Texture", 0);
}

void Paddle::Draw(const Renderer &renderer, glm::mat4 proj)
{
    glm::mat4 mvp = proj * model;
    Shader& paddleShader = ShaderManager::Get(shaderName);
    paddleShader.Bind();
    paddleShader.setUniformMat4f("u_MVP", mvp);
    setTextureUniform();
    renderer.Draw(*vao, *vbo, *ebo, paddleShader, *texture);
}

void Paddle::cleanup(){
    vao->Delete();
    vbo->Delete();
    ebo->Delete();
}

