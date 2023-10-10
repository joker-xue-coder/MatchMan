#include "RectangleDrawer.h"
#include "Shaderer.h"
#include "Renderer.h"

#include "stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int VBO, VAO, EBO;

RectangleDrawer::RectangleDrawer(Renderer* parent,int zIndex)
	:Drawer(parent)
{
	this->m_ShadererProgram = new Shaderer("RectangleShader.shader");
#pragma region 初始化一个顶点数组对象用于测试一个窗口分屏

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,1.0f, 1.0f,  // top right
		 0.5f, -0.5f, 0.0f,1.0f,0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,0.0f,0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,0.0f,1.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
#pragma endregion
	std::string imgMax = "containerA.jpg";
	//std::string imgMin = "Headache.jpg";
	std::string imgMin = "awesomeface.jpg";
#pragma region 使用Texturer来完成纹理的创建
	this->m_Texturer = new Texturer(imgMax);
	stbi_set_flip_vertically_on_load(true);
	this->m_TextureDataMax = stbi_load(imgMax.c_str(), &this->m_MaxWidth, &this->m_MaxHeight, &this->m_MaxChannel, 0);
	this->m_TextureDataMin = stbi_load(imgMin.c_str(), &this->m_MinWidth, &this->m_MinHeight, &this->m_MinChannel, 0);
#pragma endregion


}




RectangleDrawer::~RectangleDrawer()
{

	stbi_image_free(this->m_TextureDataMax);
	stbi_image_free(this->m_TextureDataMin);
}

void RectangleDrawer::ProcessInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{

	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		this->m_Texturer->RefreshSubTextureData(this->m_MaxWidth, this->m_MaxHeight, this->m_TextureDataMax);
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		this->m_Texturer->RefreshSubTextureData(this->m_MinWidth, this->m_MinHeight, this->m_TextureDataMin);
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{

	}
}

void RectangleDrawer::Draw()
{
	this->m_Texturer->Bind();
	this->m_ShadererProgram->Bind();
	glm::mat4 trans = glm::mat4(1.0f);
	glm::vec3 translateVec = glm::vec3(sin((float)glfwGetTime()), 0.0f, 0.0f);
	trans = glm::translate(trans, translateVec);
	this->m_ShadererProgram->SetUniformMat4f("rectangleTransform", trans);
	this->m_ShadererProgram->SetUniform1i("ourTexture", 0);
	//this->m_ShadererProgram->SetUniform1f("color", 1.0f);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	this->m_ShadererProgram->Unbind();
	this->m_Texturer->Unbind();
}
