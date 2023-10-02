#include "VertexBuffer.h"




VertexBuffer::VertexBuffer(void* verticesData, unsigned int dataSize,GLenum usage)
	:m_VerticesData(verticesData),m_VerticesDataSize(dataSize),m_Usage(usage)
{
	glGenBuffers(1, &this->m_VertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, this->m_VerticesDataSize, this->m_VerticesData, this->m_Usage);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &this->m_VertexBufferID);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->m_VertexBufferID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
