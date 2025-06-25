#include "ball.h"
#include "../res/shaders/shaderManager.h"


Ball::Ball(float screenWidth, float screenHeight, float radius, float xStart, float yStart, std::string shaderName) : 
radius(radius), x(xStart), y(yStart), shaderName(shaderName)
{
    vertices = {
        -radius, -radius, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        radius, -radius, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        radius, radius, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -radius, radius, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
    };

    indices = {
        0, 1, 2,
        2, 3, 0
    };
    vao = new VAO();
    vbo = new VBO(vertices, false);
    ebo = new EBO(indices);
    texture = new Texture("../res/textures/yellowball.png");
    model = glm::mat4(1.0f);

    vao->Bind();
    vao->LinkVBO(*vbo, 0);
    ebo->Bind();
    texture->Bind();

    vao->Unbind();
    vbo->Unbind();
    ebo->Unbind();
    texture->Unbind();

    xv = 0.0f;
    yv = 0.0f;
    xDir = 1.0f;
    yDir = 1.0f;

}

Ball::~Ball()
{
    delete vao;
    delete vbo;
    delete ebo;
    delete texture;
}

bool Ball::checkOutOfBounds(float screenWidth, float screenHeight, float changeX, float changeY)
{
    float newX = x + changeX;
    float newY = y + changeY;
    if(newX > screenWidth || newX < 0.0f)
    {
        changeX *= -1;
        return true;
    }
    if(newY > screenHeight)
    {
        return true;
        changeY *= -1;
    }
    if(newY < 0.0f)
    {

    }
    return false;
}

void Ball::update(float changeX, float changeY, float speed)
{
    float newX = x + (changeX * xv);
    float newY = y + (changeY * yv);
    if(newX > 800.0f || newX < 0.0f)
    {
        xv *= -1;
    }
    if(newY > 800.0f)
    {
        yv *= -1;
    }
    if(newY < 0.0f)
    {
        x = 400.0f;
        y = 60.0f;
        xv = 0.0f;
        yv = 0.0f;
        model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
        return;
    }
    x += (changeX * xv);
    y += (changeY * yv);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
}

void Ball::setTextureUniform()
{
    Shader& shader = ShaderManager::Get(shaderName);
    shader.Bind();
    shader.setUniform1i("u_Texture", 0);
}

void Ball::Draw(const Renderer& renderer, glm::mat4 proj)
{
    glm::mat4 mvp = proj * model;
    Shader& shader = ShaderManager::Get(shaderName);
    shader.Bind();
    shader.setUniform1i("u_Texture", 0);
    shader.setUniformMat4f("u_MVP", mvp);
    renderer.Draw(*vao, *vbo, *ebo, shader, *texture);
}
