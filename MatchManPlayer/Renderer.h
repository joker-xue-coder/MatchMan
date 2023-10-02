#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <list>

#include "Drawer.h"
class RenderWindower;

class Renderer
{
public:
	Renderer(RenderWindower* parent);
	~Renderer();

	void Render();

	void AddSubDrawer(Drawer* drawer);

protected:
private:
	RenderWindower* m_ParentRenderWindow;
	std::list<Drawer*> m_SubDrawers;
};

#endif
