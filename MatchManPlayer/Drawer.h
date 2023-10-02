#ifndef _DRAWER_H_
#define _DRAWER_H_

class Renderer;

class Drawer
{
public:
	Drawer(Renderer* parent);
	~Drawer();

	virtual void Draw() = 0;
protected:
	Renderer* m_ParentRenderer;
	int m_ZIndex;
private:
};
#endif

