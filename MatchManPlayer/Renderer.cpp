#include "Renderer.h"
#include "RenderWindower.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>


Renderer::Renderer(RenderWindower * parent)
	:m_ParentRenderWindow(parent)
{
	this->m_ParentRenderWindow->AddSubRenderer(this);


}

Renderer::~Renderer()
{
}

void Renderer::ProcessInput(GLFWwindow * window)
{
	std::list<Drawer*>::iterator iter;
	for (iter = this->m_SubDrawers.begin(); iter != this->m_SubDrawers.end(); iter++)
	{
		(*iter)->ProcessInput(window);
	}
}

void Renderer::Render()
{
	std::list<Drawer*>::iterator iter;
	for (iter = this->m_SubDrawers.begin(); iter != this->m_SubDrawers.end(); iter++)
	{
		(*iter)->Draw();
	}

}

void Renderer::AddSubDrawer(Drawer * drawer)
{
	this->m_SubDrawers.push_back(drawer);
}
