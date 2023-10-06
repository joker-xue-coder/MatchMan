#pragma once
#include "Drawer.h"
#include "Common.h"
#include "stb_truetype.h"
#include "Shaderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texturer.h"

class TextDrawer :
	public Drawer
{
public:
	TextDrawer(Renderer* parent,std::string fontPath);
	~TextDrawer();
	virtual void Draw();
	virtual void ProcessInput(GLFWwindow *window);
	void InitTexturers();
private:
	void LoadFont();


	void DrawText(const char* text, float x, float y, float size);
	void DrawRect();

	Texturer* FindCharTexturer(std::string ch);

	int UTF8ToUnicode(const char* text, int length);
private:
	std::string m_FontFilePath;
	char* m_Text;
	stbtt_fontinfo font;
	Shaderer* m_Shaderer;

	VertexBuffer* m_RectVBO;
	VertexArray* m_RectVAO;

	unsigned int VAO, VBO;
	static std::map<std::string, Texturer*> m_TextTexturers;
};