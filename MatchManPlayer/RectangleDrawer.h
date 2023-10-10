#pragma once
#include "Drawer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texturer.h"

class Shaderer;
class Renderer;

class RectangleDrawer :
	public Drawer
{
public:
	RectangleDrawer(Renderer* parent,int zIndex=0);
	~RectangleDrawer();

	virtual void ProcessInput(GLFWwindow *window);
	
	virtual void Draw();
protected:
private:
	Shaderer* m_ShadererProgram;
	Texturer* m_Texturer;
	unsigned char* m_TextureDataMax;
	int m_MaxWidth;
	int m_MaxHeight;
	int m_MaxChannel;
	unsigned char* m_TextureDataMin;
	int m_MinWidth;
	int m_MinHeight;
	int m_MinChannel;

};

