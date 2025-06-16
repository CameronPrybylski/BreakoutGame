#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "glad/glad.h"

#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "../../res/shaders/shaderClass.h"
#include "texture.h"

class Renderer{

public:

    void Clear() const;
    void Draw(const VAO& vao, const VBO& vbo, const EBO& ebo, const Shader& shader, const Texture& texture) const;

};

#endif