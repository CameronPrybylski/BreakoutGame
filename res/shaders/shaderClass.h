#ifndef _SHADER_CLASS_H_
#define _SHADER_CLASS_H_

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>
#include<unordered_map>

std::string get_file_contents(const char* filename);

class Shader
{
private:
	std::unordered_map<const char*, int> uniformLoactionsCache;
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);
    ~Shader();

	// Activates the Shader Program
	void Bind() const;
	// Deactivates the Shader Program
	void Unbind();
	// Deletes the Shader Program
	void Delete();

	int getUniformLocation(const char* uniformName);
	void setUniform4f(const char* uniformName, float v0, float v1, float v2, float v3);
	void setUniform1i(const char* uniformName, int value);
};

#endif