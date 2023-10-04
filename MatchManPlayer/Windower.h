#ifndef _WINDOWER_H_
#define _WINDOWER_H_

#include "Common.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <list>
/************************************************************************/
/* 管理窗口																*/
/* 窗口大小																*/
/* 窗口交互																*/
/************************************************************************/

class RenderWindower;

class Windower
{
public:
	Windower(GLFWwindow* window=nullptr,int width=800,int height=600,std::string name="Hello Windower");
	~Windower();
	GLFWwindow* GetGLFWwindow();

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	void Render();

	void AddSubRenderWindower(RenderWindower* subWindower);


protected:
private:
	void Init();
	void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
private:
	GLFWwindow* m_Window;
	std::string m_Name;
	unsigned int m_Width;
	unsigned int m_Height;
	int m_State;

	std::list<RenderWindower*> m_SubRenderWindowers;

};

#endif
