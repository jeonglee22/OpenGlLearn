#pragma once
#include "pch.h"
#include "VBO.h"

class VAO
{
public:
	VAO();
	VAO(unsigned int number);

	~VAO() { glDeleteVertexArrays(arraySize, &ID); }

	void Bind();
	void UnBind();
	void LinkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents,
		GLenum type, GLsizeiptr stride, void* offset);

private:
	unsigned int ID;
	unsigned int arraySize;
};

