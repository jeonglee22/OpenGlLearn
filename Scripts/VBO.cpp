#include "VBO.h"

VBO::VBO() : bufferSize(1), target(GL_ARRAY_BUFFER)
{
	glGenBuffers(1, &ID);
}

VBO::VBO(GLenum target, const void *data, GLsizeiptr size, GLenum usage)
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

void VBO::SetBuffer(GLenum target, const void *data, GLsizeiptr size, GLenum usage)
{
	this->target = target;
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
