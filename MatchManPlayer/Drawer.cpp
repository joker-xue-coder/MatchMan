#include "Drawer.h"
#include "Renderer.h"
Drawer::Drawer(Renderer * parent)
	:m_ParentRenderer(parent),m_ZIndex(0)
{
	this->m_ParentRenderer->AddSubDrawer(this);
}

Drawer::~Drawer()
{
}

