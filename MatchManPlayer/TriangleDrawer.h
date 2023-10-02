#pragma once
#include "Drawer.h"

class Shaderer;
class VertexArray;
class VertexBuffer;

class TriangleDrawer :
	public Drawer
{
public:
	TriangleDrawer(Renderer* parent,int zIndex=0);
	~TriangleDrawer();

	virtual void Draw();
protected:
private:
	Shaderer* m_ShadererProgram;
	VertexArray* m_VAO;
	VertexBuffer* m_VBO;
};

