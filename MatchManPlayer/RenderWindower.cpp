#include "RenderWindower.h"
#include "Windower.h"
#include "Renderer.h"


RenderWindower::RenderWindower(Windower * parent, int width, int height, int x, int y, int zIndex)
	:m_ParentWindower(parent),m_Width(width),m_Height(height),m_X(x),m_Y(y),m_ZIndex(zIndex)
{
	this->m_ParentWindower->AddSubRenderWindower(this);
}

RenderWindower::~RenderWindower()
{
}

//渲染之前必须要先设定渲染窗口的位置和大小，即确认渲染的矩形框
void RenderWindower::Render()
{
	this->SetViewPort();
	if (this->m_SubRenderer != nullptr)
	{
		this->m_SubRenderer->Render();
	}
}

void RenderWindower::AddSubRenderer(Renderer * subRenderer)
{
	this->m_SubRenderer = subRenderer;
}

void RenderWindower::SetViewPort()
{
	glViewport(this->m_X, this->m_Y, this->m_Width, this->m_Height);
}
