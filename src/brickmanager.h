#ifndef _BRICKMANAGER_H_
#define _BRICKMANAGER_H_


#include "brick.h"
#include<string>

class BrickManager {

private:
    std::vector<Brick> bricks;
    std::vector<float> vertices;
    VAO* vao;
    VBO* vbo;
    EBO* ebo;
    Texture* texture;
    std::string shaderName;


public:
    BrickManager(std::vector<Brick> bricks, std::string shaderName);
    ~BrickManager();
    void setTextureUniform();
    void Draw(const Renderer& renderer, glm::mat4 proj);
    std::vector<Brick> getBricks(){return bricks;}
    void removeBrick(int i);
    void update();

};

#endif
