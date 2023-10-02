#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
class VertexBuffer
{
public:
	VertexBuffer(void* verticesData,unsigned int dataSize,GLenum usage= GL_STATIC_DRAW);
	~VertexBuffer();

	void Bind();
	void Unbind();

protected:
private:
	void* m_VerticesData;
	unsigned int m_VerticesDataSize;
	unsigned int m_VertexBufferID;
	GLenum m_Usage;
};

