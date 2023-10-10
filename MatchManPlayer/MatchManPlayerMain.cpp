#include "Common.h"
#include "Windower.h"
#include "RenderWindower.h"
#include "Renderer.h"
#include "TriangleDrawer.h"
#include "RectangleDrawer.h"
#include "MatchManDrawer.h"
#include "TextDrawer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;




int main(int argc,char* argv[],char* env[])
{

	PrintLog(argv[0]);


	Windower* windower = new Windower;


#pragma region ËÄ´°¿Úµ÷ÊÔ


	////×óÏÂ½ÇäÖÈ¾´°¿Ú
	//RenderWindower* renderwindower = new RenderWindower(windower,400,300,0,0);
	//Renderer* renderer = new Renderer(renderwindower);
	//TriangleDrawer* tridrawer = new TriangleDrawer(renderer);

	////ÓÒÏÂ½ÇäÖÈ¾´°¿Ú
	//RenderWindower* renderwindower1 = new RenderWindower(windower, 400, 300, 400, 0);
	//Renderer* renderer1 = new Renderer(renderwindower1);
	//RectangleDrawer* rectdrawer = new RectangleDrawer(renderer1);

	////ÓÒÉÏ½ÇäÖÈ¾´°¿Ú
	//RenderWindower* renderwindower2 = new RenderWindower(windower, 300, 300, 400, 300);
	//Renderer* renderer2 = new Renderer(renderwindower2);

	//RectangleDrawer* rectdrawer1 = new RectangleDrawer(renderer2);
	//MatchManDrawer* matchman = new MatchManDrawer(renderer2);

	////×óÉÏ½ÇäÖÈ¾´°¿Ú
	//RenderWindower* renderwindower3 = new RenderWindower(windower, 400, 300, 0, 300);
	//Renderer* renderer3 = new Renderer(renderwindower3);
#pragma endregion


#pragma region »ð²ñÈËµ÷ÊÔ£¨×ó±ß£©
	RenderWindower* renderwindower2 = new RenderWindower(windower, 600, 600, 0, 0);
	Renderer* renderer2 = new Renderer(renderwindower2);

	RectangleDrawer* rectdrawer1 = new RectangleDrawer(renderer2);
	MatchManDrawer* matchman = new MatchManDrawer(renderer2);
#pragma endregion
#pragma region »ð²ñÈËµ÷ÊÔ£¨ÓÒÉÏ£©
	RenderWindower* renderwindower4 = new RenderWindower(windower, 200, 200, 600, 400);
	Renderer* renderer4 = new Renderer(renderwindower4);

	RectangleDrawer* rectdrawer2 = new RectangleDrawer(renderer4);
	MatchManDrawer* matchman2 = new MatchManDrawer(renderer4);
#pragma endregion
#pragma region »ð²ñÈËµ÷ÊÔ£¨ÓÒÖÐ£©
	RenderWindower* renderwindower5 = new RenderWindower(windower, 200, 200, 600, 200);
	Renderer* renderer5 = new Renderer(renderwindower5);

	RectangleDrawer* rectdrawer3 = new RectangleDrawer(renderer5);
	MatchManDrawer* matchman3 = new MatchManDrawer(renderer5);
#pragma endregion
#pragma region »ð²ñÈËµ÷ÊÔ£¨ÓÒÏÂ£©
	RenderWindower* renderwindower6 = new RenderWindower(windower, 200, 200, 600, 0);
	Renderer* renderer6 = new Renderer(renderwindower6);

	RectangleDrawer* rectdrawer4 = new RectangleDrawer(renderer6);
	MatchManDrawer* matchman4 = new MatchManDrawer(renderer6);
#pragma endregion
#pragma region »æÖÆ×ÖÌåµ÷ÊÔ
	RenderWindower* renderwindower3 = new RenderWindower(windower, 200, 400, 600, 0);
	Renderer* renderer3 = new Renderer(renderwindower3);

	//RectangleDrawer* rectdrawer2 = new RectangleDrawer(renderer3);
	TextDrawer* textDrawer = new TextDrawer(renderer3, "xiawumanhei.ttf");
	textDrawer->InitTexturers();
#pragma endregion
	windower->Render();


	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
