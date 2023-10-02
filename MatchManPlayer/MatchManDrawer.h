#pragma once
#include "Drawer.h"
#include "Shaderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class MatchManDrawer :
	public Drawer
{
public:
	MatchManDrawer(Renderer* parent);
	~MatchManDrawer();

	virtual void Draw();
protected:
private:
	void Init();
	void HeadInit();
	void HeadDraw();
	void LeftHandInit();
	void LeftHandDraw();
	void RightHandInit();
	void RightHandDraw();
	void BodyInit();
	void BodyDraw();
	void LeftFootInit();
	void LeftFootDraw();
	void RightFootInit();
	void RightFootDraw();
	void JointInit();
	void JonitDraw();
	void FrameInit();
	void FrameDraw();


public:
protected:
private:
	Shaderer* m_Shaderer;
	Shaderer* m_RightFootShaderer;
	
	float m_PointSize;
	glm::mat4 m_MatchManTransform;


	VertexAttrib* m_CommonAttr;
	
	VertexBuffer* m_HeadVBO;
	VertexArray* m_HeadVAO;

	VertexBuffer* m_LeftHandVBO;
	VertexArray* m_LeftHandVAO;

	VertexBuffer* m_RightHandVBO;
	VertexArray* m_RightHandVAO;

	VertexBuffer* m_BodyVBO;
	VertexArray* m_BodyVAO;

	VertexBuffer* m_LeftFootVBO;
	VertexArray* m_LeftFootVAO;

	VertexBuffer* m_RightFootVBO;
	VertexArray* m_RightFootVAO;

	VertexBuffer* m_JointVBO;
	VertexArray* m_JointVAO;

	VertexBuffer* m_FrameVBO;
	VertexArray* m_FrameVAO;

};

