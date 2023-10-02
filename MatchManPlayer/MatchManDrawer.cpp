#include "MatchManDrawer.h"

#define M_PI       3.14159265358979323846   // pi

MatchManDrawer::MatchManDrawer(Renderer* parent)
	:Drawer(parent)
{
	this->m_Shaderer = new Shaderer("noColorShader.shader");
	this->m_RightFootShaderer = new Shaderer("RightFootShader.shader");
	this->m_CommonAttr = new VertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	this->m_Shaderer->Bind();
	this->m_MatchManTransform = glm::mat4(1.0f);
	this->m_Shaderer->SetUniformMat4f("matchManTransform", this->m_MatchManTransform);
	this->m_Shaderer->Unbind();
	this->m_PointSize = 5.0f;
	this->Init();
}

MatchManDrawer::~MatchManDrawer()
{
}

void MatchManDrawer::Draw()
{
	this->HeadDraw();
	this->LeftHandDraw();
	this->RightHandDraw();
	this->BodyDraw();
	this->LeftFootDraw();
	this->RightFootDraw();
	this->JonitDraw();
	this->FrameDraw();
}

void MatchManDrawer::Init()
{
	this->HeadInit();
	this->LeftHandInit();
	this->RightHandInit();
	this->BodyInit();
	this->LeftFootInit();
	this->RightFootInit();
	this->JointInit();
	this->FrameInit();
}

void MatchManDrawer::HeadInit()
{
	float vertices[362 * 3];
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = 0;

	for (int i = 1; i <= 362 - 1; i++)
	{
		int index = i * 3;
		vertices[index] = sin(i * M_PI / 180.0f)*0.1f;
		vertices[index + 1] = cos(i * M_PI / 180.0f)*0.1f;
		vertices[index + 2] = 0;
	}


	this->m_HeadVBO = new VertexBuffer(vertices, sizeof(vertices));
	this->m_HeadVAO = new VertexArray(this->m_HeadVBO);
	this->m_HeadVAO->AddVertexAttrib(this->m_CommonAttr);

}

void MatchManDrawer::HeadDraw()
{
	this->m_Shaderer->Bind();
	this->m_HeadVAO->Bind();
	glDrawArrays(GL_TRIANGLE_FAN, 0, 362);
	this->m_HeadVAO->Unbind();
	this->m_Shaderer->Unbind();
}

void MatchManDrawer::LeftHandInit()
{
	int result = 0;
	float vertices[] =
	{
		0.0f,-0.2f,0.0f,
		-0.2f,-0.2f,0.0f,
		-0.4f,-0.2f,0.0f,
	};

	this->m_LeftHandVBO = new VertexBuffer(vertices, sizeof(vertices));
	this->m_LeftHandVAO = new VertexArray(this->m_LeftHandVBO);
	this->m_LeftHandVAO->AddVertexAttrib(this->m_CommonAttr);

}

void MatchManDrawer::LeftHandDraw()
{
	this->m_Shaderer->Bind();
	this->m_LeftHandVAO->Bind();
	glDrawArrays(GL_LINE_STRIP, 0, 3);
	this->m_LeftHandVAO->Unbind();
	this->m_Shaderer->Unbind();
}

void MatchManDrawer::RightHandInit()
{
	int result = 0;
	float vertices[] =
	{
		0.0f,-0.2f,0.0f,
		0.2f,-0.2f,0.0f,
		0.4f,-0.2f,0.0f,
	};

	this->m_RightHandVBO = new VertexBuffer(vertices, sizeof(vertices));
	this->m_RightHandVAO = new VertexArray(this->m_RightHandVBO);
	this->m_RightHandVAO->AddVertexAttrib(this->m_CommonAttr);
}

void MatchManDrawer::RightHandDraw()
{
	this->m_Shaderer->Bind();
	this->m_RightHandVAO->Bind();
	glDrawArrays(GL_LINE_STRIP, 0, 3);
	this->m_RightHandVAO->Unbind();
	this->m_Shaderer->Unbind();
}

void MatchManDrawer::BodyInit()
{
	float vertices[] =
	{
		0.0f,-0.1f,0.0f,
		0.0f,-0.2f,0.0f,
		0.0f,-0.3f,0.0f,
		0.0f,-0.4f,0.0f,
	};
	this->m_BodyVBO = new VertexBuffer(vertices, sizeof(vertices));
	this->m_BodyVAO = new VertexArray(this->m_BodyVBO);
	this->m_BodyVAO->AddVertexAttrib(this->m_CommonAttr);
}

void MatchManDrawer::BodyDraw()
{
	this->m_Shaderer->Bind();
	this->m_BodyVAO->Bind();
	glDrawArrays(GL_LINE_STRIP, 0, 4);
	this->m_BodyVAO->Unbind();
	this->m_Shaderer->Unbind();
}

void MatchManDrawer::LeftFootInit()
{
	float vertices[] =
	{
		0.0f,-0.4f,0.0f,
		-0.2f,-0.6f,0.0f,
		-0.2f,-0.8f,0.0f,
	};
	this->m_LeftFootVBO = new VertexBuffer(vertices, sizeof(vertices));
	this->m_LeftFootVAO = new VertexArray(this->m_LeftFootVBO);
	this->m_LeftFootVAO->AddVertexAttrib(this->m_CommonAttr);
}

void MatchManDrawer::LeftFootDraw()
{
	this->m_Shaderer->Bind();
	this->m_LeftFootVAO->Bind();
	glDrawArrays(GL_LINE_STRIP, 0, 3);
	this->m_LeftFootVAO->Unbind();
	this->m_Shaderer->Unbind();
}

void MatchManDrawer::RightFootInit()
{
	float vertices[] =
	{
		0.0f,-0.4f,0.0f,
		0.2f,-0.6f,0.0f,
		0.2f,-0.8f,0.0f,
	};
	this->m_RightFootVBO = new VertexBuffer(vertices, sizeof(vertices));
	this->m_RightFootVAO = new VertexArray(this->m_RightFootVBO);
	this->m_RightFootVAO->AddVertexAttrib(this->m_CommonAttr);

}

void MatchManDrawer::RightFootDraw()
{
	//this->m_Shaderer->Bind();
	this->m_RightFootShaderer->Bind();
	this->m_RightFootVAO->Bind();
	glm::mat4 trans(1.0f);
	static float angle = 0.0f;
	if (angle >= 360.0f)
	{
		angle = 0.0f;
	}
	else
	{
		angle += 1.0f;
	}
	trans = glm::translate(trans, glm::vec3(0.0f, -0.4f, 0.0f));
	trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	trans = glm::translate(trans, glm::vec3(0.0f, 0.4f, 0.0f));
	this->m_RightFootShaderer->SetUniformMat4f("rightFootTransform", trans);
	this->m_RightFootShaderer->SetUniformMat4f("matchManTransform", this->m_MatchManTransform);
	this->m_RightFootShaderer->SetUniform1i("flag", 1);
	
	glDrawArrays(GL_LINE_STRIP, 0, 3);
	glPointSize(this->m_PointSize);
	glDrawArrays(GL_POINTS, 0, 3);
	this->m_RightFootVAO->Unbind();
	this->m_RightFootShaderer->Unbind();
}

void MatchManDrawer::JointInit()
{
	//float vertices[] =
	//{
	//	0.0f,0.0f,0.0f,
	//	0.0f,-0.1f,0.0f,
	//	0.0f,-0.2f,0.0f,
	//	0.0f,-0.3f,0.0f,
	//	0.0f,-0.4f,0.0f,
	//	-0.2f,-0.2f,0.0f,
	//	-0.4f,-0.2f,0.0f,
	//	0.2f,-0.2f,0.0f,
	//	0.4f,-0.2f,0.0f,
	//	-0.2f,-0.6f,0.0f,
	//	-0.2f,-0.8f,0.0f,
	//	0.2f,-0.6f,0.0f,
	//	0.2f,-0.8f,0.0f
	//};
	//this->m_JointVBO = new VertexBuffer(vertices, sizeof(vertices));
	//this->m_JointVAO = new VertexArray(this->m_JointVBO);
	//this->m_JointVAO->AddVertexAttrib(this->m_CommonAttr);
}

void MatchManDrawer::JonitDraw()
{
	//this->m_Shaderer->Bind();
	//this->m_JointVAO->Bind();
	//glDrawArrays(GL_POINTS, 0, 13);
	//this->m_JointVAO->Unbind();
	//this->m_Shaderer->Unbind();
}

void MatchManDrawer::FrameInit()
{
	float vertices[] =
	{
		-0.999f,-0.999f,0.0f,
		-0.999f,0.999f,0.0f,
		0.999f,0.999f,0.0f,
		0.999f,-0.999f,0.0f
	};
	this->m_FrameVBO = new VertexBuffer(vertices, sizeof(vertices));
	this->m_FrameVAO = new VertexArray(this->m_FrameVBO);
	this->m_FrameVAO->AddVertexAttrib(this->m_CommonAttr);
}

void MatchManDrawer::FrameDraw()
{
	this->m_Shaderer->Bind();
	this->m_FrameVAO->Bind();
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	this->m_FrameVAO->Unbind();
	this->m_Shaderer->Unbind();
}




