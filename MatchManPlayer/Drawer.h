#ifndef _DRAWER_H_
#define _DRAWER_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer;

class Drawer
{
public:
	Drawer(Renderer* parent);
	~Drawer();

	virtual void Draw() = 0;
	virtual void ProcessInput(GLFWwindow *window) {};
protected:
	Renderer* m_ParentRenderer;
	int m_ZIndex;
private:
};
#endif

