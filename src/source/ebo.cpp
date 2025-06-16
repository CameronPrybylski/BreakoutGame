#include"ebo.h"

// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO(std::vector<GLuint> indices) : count(indices.size())
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}
EBO::~EBO(){
	glDeleteBuffers(1, &ID);
}

int EBO::getCount() const{
	return count;
}

// Binds the EBO
void EBO::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}