#include "VAO.h"

VAO::VAO()
{
	glGenVertexArrays(1, &ID);
	arraySize = 1;
}

VAO::VAO(unsigned int number)
{
	glGenVertexArrays(number, &ID);
	arraySize = number;
}

void VAO::Bind()
{
	glBindVertexArray(ID);
}

void VAO::UnBind()
{
	glBindVertexArray(0);
}

void VAO::LinkAttrib(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
	vbo.Bind();
	glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(layout);
	vbo.UnBind();
}

