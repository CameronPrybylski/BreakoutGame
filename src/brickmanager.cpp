#include "brickmanager.h"
#include "../res/shaders/shaderManager.h"


BrickManager::BrickManager(std::vector<Brick> bricks, std::string shaderName) : bricks(bricks), shaderName(shaderName)
{
    vao = new VAO();
    //std::vector<float> vertices;
    for(Brick& brick : bricks){
        std::vector<float> brickVertices = brick.getVertices();
        for(float vertex : brickVertices){
            vertices.push_back(vertex);
        }
    }
    vbo = new VBO(vertices, false);
    std::vector<unsigned int> indices;
    unsigned int index = 0;
    for(int i = 0; i < bricks.size(); i++){
        indices.push_back(index);
        indices.push_back(index+1);
        indices.push_back(index+2);

        indices.push_back(index+2);
        indices.push_back(index+3);
        indices.push_back(index);

        index += 4;
    }
    ebo = new EBO(indices);

    vao->Bind();
    vao->LinkVBO(*vbo, 0);
    ebo->Bind();
    texture = new Texture("../res/textures/silverbrick.png");
    texture->Bind(0);
}

BrickManager::~BrickManager()
{
    delete vao;
    delete vbo;
    delete ebo;
}

void BrickManager::removeBrick(int i)
{
    bricks.erase(bricks.begin()+i);
    vertices.erase(vertices.begin() + (i * 32), vertices.begin() + ((i * 32) + 32));
    vbo->Bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(float), vertices.data());
}

void BrickManager::update()
{

}

void BrickManager::setTextureUniform()
{
    Shader& brickShader = ShaderManager::Get(shaderName);
    brickShader.Bind();
    brickShader.setUniform1i("u_Texture", 0);
}

void BrickManager::Draw(const Renderer& renderer, glm::mat4 proj)
{
    glm::mat4 mvp = proj * glm::mat4(1.0f);
    Shader& brickShader = ShaderManager::Get(shaderName);
    brickShader.Bind();
    brickShader.setUniformMat4f("u_MVP", mvp);
    setTextureUniform();
    renderer.Draw(*vao, *vbo, *ebo, brickShader, *texture);
}
