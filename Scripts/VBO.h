#pragma once
#include "pch.h"

class VBO
{
public:
	VBO();
	VBO(GLenum target, const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);
	VBO(unsigned int bufferSize, GLenum target, const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);

	VBO(const VBO&) = delete;
	VBO& operator=(const VBO&) = delete;

	VBO(VBO&& other) noexcept : ID(other.ID), bufferSize(other.bufferSize), target(other.target) { other.ID = 0; other.bufferSize = 0; }
	VBO& operator=(VBO&& other) noexcept
	{
		if (this != &other) {
			glDeleteBuffers(bufferSize, &ID);
			ID = other.ID; bufferSize = other.bufferSize; target = other.target;
			other.ID = 0; other.bufferSize = 0;
		}
		return *this;
	}

	~VBO() { glDeleteBuffers(bufferSize, &ID); }

	void Bind() const;
	void UnBind() const;
	void SetBuffer(GLenum target, const void* data, GLsizeiptr size, GLenum usage = GL_STATIC_DRAW);

private:
	unsigned int ID;
	unsigned int bufferSize;
	GLenum target;

};

