#pragma once
#include "Common.h"
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
	virtual void ProcessInput(GLFWwindow *window);
protected:
private:
	void Init();

	void ShadererInit();
	void TransformInit();
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

	void Rotate(glm::mat4& transform, glm::vec3 rotate_center,float angle);

	void Walk();


public:
protected:
private:
	unsigned int texture;
	std::vector<glm::vec3> m_Joints;



	Shaderer* m_Shaderer;
	Shaderer* m_HeadShaderer;
	Shaderer* m_RightFootShaderer;
	Shaderer* m_LeftFootShaderer;
	Shaderer* m_RightHandShaderer;
	Shaderer* m_LeftHandShaderer;
	Shaderer* m_FrameShaderer;

	
	float m_PointSize;
	glm::mat4 m_MatchManTransform;
	glm::mat4 m_HeadTransform;

	glm::mat4 m_RightFootTransform0;
	glm::mat4 m_RightFootTransform00;
	glm::mat4 m_LeftFootTransform0;
	glm::mat4 m_LeftFootTransform00;
	glm::mat4 m_RightHandTransform0;
	glm::mat4 m_RightHandTransform00;
	glm::mat4 m_LeftHandTransform0;
	glm::mat4 m_LeftHandTransform00;




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

