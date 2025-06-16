#include "vao.h"

VAO::VAO(){
    glGenVertexArrays(1, &ID);
}

VAO::~VAO(){
	glDeleteVertexArrays(1, &ID);
}

// Links a VBO to the VAO using a certain layout
void VAO::LinkVBO(VBO& VBO, GLuint layout)
{
	VBO.Bind();
	glEnableVertexAttribArray(layout);
	glVertexAttribPointer(layout, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); //position
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); //tex coord
	VBO.Unbind();
}

// Binds the VAO
void VAO::Bind() const
{
	glBindVertexArray(ID);
}

// Unbinds the VAO
void VAO::Unbind()
{
	glBindVertexArray(0);
}

// Deletes the VAO
void VAO::Delete()
{
	glDeleteVertexArrays(1, &ID);
}