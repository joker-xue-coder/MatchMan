#include "Windower.h"
#include "RenderWindower.h"



Windower::Windower(GLFWwindow * window, int width, int height, std::string name)
	:m_Window(window), m_Width(width), m_Height(height), m_State(0), m_Name(name)
{
	if (window == nullptr)
	{
		this->Init();
		if (m_State == -1)
		{
			PrintLog("Init Windower Failed !");
		}
	}

}

Windower::~Windower()
{
	glfwTerminate();
}

GLFWwindow * Windower::GetGLFWwindow()
{
	return this->m_Window;
}

void Windower::KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	//PrintLog("press or release key");
	//if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	//{
	//	PrintLog("press GLFW_KEY_0");
	//}
	//else if (key == GLFW_KEY_0 && action == GLFW_RELEASE)
	//{
	//	PrintLog("release GLFW_KEY_0");
	//}
}

void Windower::Render()
{
	
	PrintLog(this->m_SubRenderWindowers.size());
	while (!glfwWindowShouldClose(this->m_Window))
	{

		//会将整个窗口用该颜色刷新
		//glEnable(GL_DEPTH_TEST);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		std::list<RenderWindower*>::iterator iter;
		for (iter = this->m_SubRenderWindowers.begin(); iter != this->m_SubRenderWindowers.end(); iter++)
		{
			(*iter)->ProcessInput(this->m_Window);
			(*iter)->Render();
		}

		glfwSwapBuffers(this->m_Window);
		glfwPollEvents();
	}
}

void Windower::AddSubRenderWindower(RenderWindower * subWindower)
{
	//需要根据ZIndex进行排序,越小排在越前面,渲染画面的时候越先被渲染
	this->m_SubRenderWindowers.push_back(subWindower);
	this->m_SubRenderWindowers.sort();
}

void Windower::Init()
{

	// glfw: initialize and configure			
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);




	/*int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
*/
	// glfw window creation
	// --------------------
	PrintLog(this->m_Name.c_str());
	this->m_Window = glfwCreateWindow(this->m_Width, this->m_Height, this->m_Name.c_str(), NULL, NULL);
	if (this->m_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		m_State = -1;
		return;
	}
	glfwMakeContextCurrent(this->m_Window);
	//glfwSetFramebufferSizeCallback(this->m_Window,&Windower::FrameBufferSizeCallback);

	glfwSetKeyCallback(this->m_Window, Windower::KeyCallback);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		m_State = -1;
		return;
	}

}

void Windower::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	PrintLog("windower resize !");
}
