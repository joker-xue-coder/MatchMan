#include "VertexArray.h"
#include "VertexBuffer.h"

VertexArray::VertexArray(VertexBuffer * vertexbuffer)
	:m_VertexBuffer(vertexbuffer),m_VertexArrayID(0)
{
	glGenVertexArrays(1, &this->m_VertexArrayID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &this->m_VertexArrayID);
}

void VertexArray::Bind()
{
	glBindVertexArray(this->m_VertexArrayID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexAttrib(VertexAttrib* attrib)
{
	this->m_VertexAttribes.push_back(attrib);
	this->m_VertexBuffer->Bind();
	glBindVertexArray(this->m_VertexArrayID);
	glVertexAttribPointer(attrib->m_Location, attrib->m_AttribVecDi, attrib->m_Type, attrib->m_Normalized, attrib->m_Stride, (void*)attrib->m_Offset);
	glEnableVertexAttribArray(attrib->m_Location);
	glBindVertexArray(0);
	this->m_VertexBuffer->Unbind();
}
