#pragma once
#include "Drawer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shaderer;
class Renderer;

class RectangleDrawer :
	public Drawer
{
public:
	RectangleDrawer(Renderer* parent,int zIndex=0);
	~RectangleDrawer();
	
	virtual void Draw();
protected:
private:
	Shaderer* m_ShadererProgram;
	unsigned int texture;
};

