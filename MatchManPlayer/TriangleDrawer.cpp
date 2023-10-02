#include "TriangleDrawer.h"
#include "Shaderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h";

#include <glad/glad.h>
#include <GLFW/glfw3.h>


TriangleDrawer::TriangleDrawer(Renderer * parent,int zIndex)
	:Drawer(parent)
{
	m_ZIndex = zIndex;
	this->m_ShadererProgram = new Shaderer("myshader.shader");

	float vertices[] = 
	{
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	
	this->m_VBO = new VertexBuffer(vertices, sizeof(vertices));
	this->m_VAO = new VertexArray(this->m_VBO);
	this->m_VAO->AddVertexAttrib(new VertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0, "postion"));
	this->m_VAO->AddVertexAttrib(new VertexAttrib(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0, "color  "));
	
}

TriangleDrawer::~TriangleDrawer()
{
}

void TriangleDrawer::Draw()
{
	this->m_ShadererProgram->Bind();
	this->m_VAO->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	this->m_ShadererProgram->Unbind();
}
