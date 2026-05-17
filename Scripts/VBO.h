#pragma once
#include "pch.h"

class VBO
{
public:
	VBO();
	VBO(GLenum target, const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
	VBO(unsigned int bufferSize, GLenum target, const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
	~VBO() { glDeleteBuffers(bufferSize, &ID); }

	void Bind() const;
	void UnBind() const;
	void SetBuffer(GLenum target, const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);

private:
	unsigned int ID;
	unsigned int bufferSize;
	GLenum target;

};

