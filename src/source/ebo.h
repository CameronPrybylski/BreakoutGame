#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include<glad/glad.h>
#include<vector>

class EBO
{

private:
	int count;
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(std::vector<GLuint> indices);
    ~EBO();

	// Binds the EBO
	void Bind() const;
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();

	int getCount() const;
};

#endif