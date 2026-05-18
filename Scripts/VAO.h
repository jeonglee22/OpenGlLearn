#pragma once
#include "pch.h"
#include "VBO.h"

class VAO
{
public:
	VAO();
	VAO(unsigned int number);

	VAO(const VAO&) = delete;
	VAO& operator=(const VAO&) = delete;

	VAO(VAO&& other) noexcept : ID(other.ID), arraySize(other.arraySize) { other.ID = 0; other.arraySize = 0; }
	VAO& operator=(VAO&& other) noexcept
	{
		if (this != &other) {
			glDeleteVertexArrays(arraySize, &ID);
			ID = other.ID; arraySize = other.arraySize;
			other.ID = 0; other.arraySize = 0;
		}
		return *this;
	}

	~VAO() { glDeleteVertexArrays(arraySize, &ID); }

	void Bind();
	void UnBind();
	void LinkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents,
		GLenum type, GLsizeiptr stride, void* offset);

private:
	unsigned int ID;
	unsigned int arraySize;
};

