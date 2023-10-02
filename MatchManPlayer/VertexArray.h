#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list>
#include <string>

struct VertexAttrib 
{
	VertexAttrib(unsigned int location,
		unsigned int attribVecDi = 3,
		GLenum type = GL_FLOAT, 
		GLboolean normalized = GL_FALSE,
		unsigned int stride = 6 * sizeof(float),
		unsigned int offset = 0,
		std::string name = "attrib")
		:m_AttribName(name), m_Location(location), m_AttribVecDi(attribVecDi),
		m_Type(type), m_Normalized(normalized), m_Stride(stride), m_Offset(offset)
	{

	}
	std::string m_AttribName;
	unsigned int m_Location;
	unsigned int m_AttribVecDi;
	GLenum m_Type;
	GLboolean m_Normalized;
	unsigned int m_Stride;//一个顶点的所有属性所占的字节数
	unsigned int m_Offset;//偏移的字节数大小
};


class VertexBuffer;


class VertexArray
{
public:
	VertexArray(VertexBuffer* vertexbuffer);
	~VertexArray();

	void Bind();
	void Unbind();

	void AddVertexAttrib(VertexAttrib* attrib);

protected:
private:
	unsigned int m_VertexArrayID;
	VertexBuffer* m_VertexBuffer;
	std::list<VertexAttrib*> m_VertexAttribes;
};

