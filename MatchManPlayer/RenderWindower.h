#ifndef _RENDERWINDOWER_H_
#define _RENDERWINDOWER_H_
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Windower;
class Renderer;

class RenderWindower
{
public:
	RenderWindower(Windower* parent, int width = 400, int height = 300, int x = 0, int y = 0, int zIndex = 0);
	~RenderWindower();

	void ProcessInput(GLFWwindow* windower);

	void Render();

	void AddSubRenderer(Renderer* subRenderer);

protected:
private:
	void SetViewPort();
private:
	Windower* m_ParentWindower;
	int m_Width;
	int m_Height;
	int m_X;
	int m_Y;
	int m_ZIndex;

	Renderer* m_SubRenderer;

};

#endif
