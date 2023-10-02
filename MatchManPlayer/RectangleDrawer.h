#pragma once
#include "Drawer.h"

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
};

