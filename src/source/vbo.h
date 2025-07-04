#ifndef _VBO_H_
#define _VBO_H_

#include "glad/glad.h"
#include <vector>

class VBO {
public:

    GLuint ID;

    VBO(std::vector<GLfloat> vertices, bool staticOr);
    ~VBO();

    void Bind() const;
    void Bind(std::vector<GLfloat> vertices);
    void Unbind();
    void Delete();
};

#endif