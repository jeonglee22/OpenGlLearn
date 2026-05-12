#include "VBO.h"

VBO::VBO(GLenum target, const void* data, GLsizeiptr size, GLenum usage)
	: target(target), bufferSize(1)
{
	glGenBuffers(1, &ID);
	glBindBuffer(target, ID);
	glBufferData(target, size, data, usage);
}

VBO::VBO(unsigned int bufferSize, GLenum target, const void* data, GLsizeiptr size, GLenum usage)
	: target(target), bufferSize(bufferSize)
{
	glGenBuffers(bufferSize, &ID);
	glBindBuffer(target, ID);
	glBufferData(target, size, data, usage);
}

void VBO::Bind() const
{
	glBindBuffer(target, ID);
}

void VBO::UnBind() const
{
	glBindBuffer(target, 0);
}
