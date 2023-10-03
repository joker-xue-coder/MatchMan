#include "MatchManDrawer.h"

#define M_PI       3.14159265358979323846   // pi

MatchManDrawer::MatchManDrawer(Renderer* parent)
	:Drawer(parent)
{
	

	this->m_CommonAttr = new VertexAttrib(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	this->m_PointSize = 5.0f;
	
	this->Init();
}

MatchManDrawer::~MatchManDrawer()
{
}

void MatchManDrawer::Draw()
{
	this->Walk();
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
	this->ShadererInit();
	this->TransformInit();
	this->HeadInit();
	this->LeftHandInit();
	this->RightHandInit();
	this->BodyInit();
	this->LeftFootInit();
	this->RightFootInit();
	this->JointInit();
	this->FrameInit();
}

void MatchManDrawer::ShadererInit()
{
	this->m_Shaderer = new Shaderer("noColorShader.shader");
	this->m_RightFootShaderer = new Shaderer("RightFootShader.shader");
	this->m_LeftFootShaderer = new Shaderer("LeftFootShader.shader");
	this->m_RightHandShaderer = new Shaderer("RightHandShader.shader");
	this->m_LeftHandShaderer = new Shaderer("LeftHandShader.shader");
}

void MatchManDrawer::TransformInit()
{
	this->m_Shaderer->Bind();
	this->m_MatchManTransform = glm::mat4(1.0f);
	this->m_Shaderer->SetUniformMat4f("matchManTransform", this->m_MatchManTransform);
	this->m_Shaderer->Unbind();

	this->m_RightFootTransform0 = glm::mat4(1.0f);
	this->m_RightFootTransform00 = glm::mat4(1.0f);
	this->m_LeftFootTransform0 = glm::mat4(1.0f);
	this->m_LeftFootTransform00 = glm::mat4(1.0f);
	this->m_RightHandTransform0 = glm::mat4(1.0f);
	this->m_RightHandTransform00 = glm::mat4(1.0f);
	this->m_LeftHandTransform0 = glm::mat4(1.0f);
	this->m_LeftHandTransform00 = glm::mat4(1.0f);
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
	this->m_LeftHandShaderer->Bind();
	//this->m_Shaderer->Bind();
	this->m_LeftHandVAO->Bind();


	this->m_LeftHandShaderer->SetUniformMat4f("leftHandTransform0", this->m_LeftHandTransform0);
	this->m_LeftHandShaderer->SetUniformMat4f("leftHandTransform00", this->m_LeftHandTransform00);
	this->m_LeftHandShaderer->SetUniformMat4f("matchManTransform", this->m_MatchManTransform);



	glDrawArrays(GL_LINE_STRIP, 0, 3);
	glPointSize(this->m_PointSize);
	glDrawArrays(GL_POINTS, 0, 3);
	this->m_LeftHandVAO->Unbind();
	//this->m_Shaderer->Unbind();
	this->m_LeftHandShaderer->Unbind();
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
	//this->m_Shaderer->Bind();
	this->m_RightHandShaderer->Bind();
	this->m_RightHandVAO->Bind();

	this->m_RightHandShaderer->SetUniformMat4f("rightHandTransform0", this->m_RightHandTransform0);
	this->m_RightHandShaderer->SetUniformMat4f("rightHandTransform00", this->m_RightHandTransform00);
	this->m_LeftHandShaderer->SetUniformMat4f("matchManTransform", this->m_MatchManTransform);

	glDrawArrays(GL_LINE_STRIP, 0, 3);
	glPointSize(this->m_PointSize);
	glDrawArrays(GL_POINTS, 0, 3);
	this->m_RightHandVAO->Unbind();
	this->m_RightHandShaderer->Unbind();
	//this->m_Shaderer->Unbind();
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
	glPointSize(this->m_PointSize);
	glDrawArrays(GL_POINTS, 0, 4);
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
	this->m_LeftFootShaderer->Bind();
	this->m_LeftFootVAO->Bind();
	
	this->m_LeftFootShaderer->SetUniformMat4f("leftFootTransform0", this->m_LeftFootTransform0);
	this->m_LeftFootShaderer->SetUniformMat4f("leftFootTransform00", this->m_LeftFootTransform00);
	this->m_LeftFootShaderer->SetUniformMat4f("matchManTransform", this->m_MatchManTransform);
	
	glDrawArrays(GL_LINE_STRIP, 0, 3);
	glPointSize(this->m_PointSize);
	glDrawArrays(GL_POINTS, 0, 3);
	this->m_LeftFootVAO->Unbind();
	this->m_LeftFootShaderer->Unbind();
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
#pragma region 绘制初始状态的右脚
	//this->m_Shaderer->Bind();
	//this->m_RightFootVAO->Bind();
	//glDrawArrays(GL_LINE_STRIP, 0, 3);
	//glPointSize(this->m_PointSize);
	//glDrawArrays(GL_POINTS, 0, 3);
	//this->m_RightFootVAO->Unbind();
	//this->m_Shaderer->Unbind();
#pragma endregion


	this->m_RightFootShaderer->Bind();
	this->m_RightFootVAO->Bind();


	this->m_RightFootShaderer->SetUniformMat4f("rightFootTransform0", this->m_RightFootTransform0);
	this->m_RightFootShaderer->SetUniformMat4f("rightFootTransform00", this->m_RightFootTransform00);
	this->m_RightFootShaderer->SetUniformMat4f("matchManTransform", this->m_MatchManTransform);
	
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


/*
仅适用于二维的旋转
*/
void MatchManDrawer::Rotate(glm::mat4 & transform, glm::vec3 rotate_center,float angle)
{

	//glm::vec3 translate_vec(rotate_center.x*(-1.0f), rotate_center.y*(-1.0f), rotate_center.z*(-1.0f));
	glm::vec3 translate_vec = rotate_center * (-1.0f);
	
	//旋转的变换顺序如下
	//3.将旋转中心移动到原来的位置，这样旋转完成之后就是绕指定的旋转中心旋转后的结果了
	transform = glm::translate(transform, rotate_center);
	//2.二维旋转直接绕坐标系原点旋转，完成旋转动作
	transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
	//1.将旋转中心移动到坐标系原点
	transform = glm::translate(transform, glm::vec3(translate_vec));
}

void MatchManDrawer::Walk()
{
	static int flag = 0;
	static float angle0 = 0.0f;
	static float angle00 = 45.0f;
	glm::mat4 trans0 = glm::mat4(1.0f);
	glm::mat4 trans00 = glm::mat4(1.0f);
	glm::vec3 rotateCenter0;
	glm::vec3 rotateCenter00;
	//if (angle1 >= 360.0f)
	//{
	//	angle1 = 0.0f;
	//}
	//else
	//{
	//	angle1 += 1.0f;
	//}
	if (flag % 100 == 0)
	{
		//右脚抬起
		angle0 = 0.0f;
		angle00 = 45.0f;
		rotateCenter0 = glm::vec3(0.0f, -0.4f, 0.0f);
		rotateCenter00 = glm::vec3(0.2f, -0.6f, 0.0f);
		this->Rotate(trans0, rotateCenter0, angle0);
		this->Rotate(trans00, rotateCenter00, angle00);
		this->m_RightFootTransform0 = trans0;
		this->m_RightFootTransform00 = trans00;
		//左脚落地
		trans0 = glm::mat4(1.0f);
		trans00 = glm::mat4(1.0f);
		angle0 = 45.0f;
		angle00 = -45.0f;
		rotateCenter0 = glm::vec3(0.0f, -0.4f, 0.0f);
		rotateCenter00 = glm::vec3(-0.2f, -0.6f, 0.0f);
		this->Rotate(trans0, rotateCenter0, angle0);
		this->Rotate(trans00, rotateCenter00, angle00);
		this->m_LeftFootTransform0 = trans0;
		this->m_LeftFootTransform00 = trans00;

		//左手插兜
		trans0 = glm::mat4(1.0f);
		trans00 = glm::mat4(1.0f);
		angle0 = 45.0f;
		angle00 = 0.0f;
		rotateCenter0 = glm::vec3(0.0f, -0.2f, 0.0f);
		rotateCenter00 = glm::vec3(-0.2f, -0.2f, 0.0f);
		this->Rotate(trans0, rotateCenter0, angle0);
		//this->Rotate(trans00, rotateCenter00, angle00);
		this->m_LeftHandTransform0 = trans0;
		this->m_LeftHandTransform00 = trans00;

		//右手插兜
		trans0 = glm::mat4(1.0f);
		trans00 = glm::mat4(1.0f);
		angle0 = -45.0f;
		angle00 = 0.0f;
		rotateCenter0 = glm::vec3(0.0f, -0.2f, 0.0f);
		rotateCenter00 = glm::vec3(0.2f, -0.2f, 0.0f);
		this->Rotate(trans0, rotateCenter0, angle0);
		//this->Rotate(trans00, rotateCenter00, angle00);
		this->m_RightHandTransform0 = trans0;
		this->m_RightHandTransform00 = trans00;
	}
	else
	{
		//右脚落地
		angle0 = -45.0f;
		angle00 = 45.0f;
		rotateCenter0 = glm::vec3(0.0f, -0.4f, 0.0f);
		rotateCenter00 = glm::vec3(0.2f, -0.6f, 0.0f);
		this->Rotate(trans0, rotateCenter0, angle0);
		this->Rotate(trans00, rotateCenter00, angle00);
		this->m_RightFootTransform0 = trans0;
		this->m_RightFootTransform00 = trans00;
		//左脚抬起
		trans0 = glm::mat4(1.0f);
		trans00 = glm::mat4(1.0f);
		angle0 = 0.0f;
		angle00 = -45.0f;
		rotateCenter0 = glm::vec3(0.0f, -0.4f, 0.0f);
		rotateCenter00 = glm::vec3(-0.2f, -0.6f, 0.0f);
		this->Rotate(trans0, rotateCenter0, angle0);
		this->Rotate(trans00, rotateCenter00, angle00);
		this->m_LeftFootTransform0 = trans0;
		this->m_LeftFootTransform00 = trans00;

		//左手插兜
		trans0 = glm::mat4(1.0f);
		trans00 = glm::mat4(1.0f);
		angle0 = 45.0f;
		angle00 = 0.0f;
		rotateCenter0 = glm::vec3(0.0f, -0.2f, 0.0f);
		rotateCenter00 = glm::vec3(-0.2f, -0.2f, 0.0f);
		this->Rotate(trans0, rotateCenter0, angle0);
		//this->Rotate(trans00, rotateCenter00, angle00);
		this->m_LeftHandTransform0 = trans0;
		this->m_LeftHandTransform00 = trans00;

		//右手插兜
		trans0 = glm::mat4(1.0f);
		trans00 = glm::mat4(1.0f);
		angle0 = -45.0f;
		angle00 = 0.0f;
		rotateCenter0 = glm::vec3(0.0f, -0.2f, 0.0f);
		rotateCenter00 = glm::vec3(0.2f, -0.2f, 0.0f);
		this->Rotate(trans0, rotateCenter0, angle0);
		//this->Rotate(trans00, rotateCenter00, angle00);
		this->m_RightHandTransform0 = trans0;
		this->m_RightHandTransform00 = trans00;
	}
	flag++;
}




