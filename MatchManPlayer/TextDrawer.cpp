#define _CRT_SECURE_NO_WARNINGS
#include "TextDrawer.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

std::map<std::string, Texturer*> TextDrawer::m_TextTexturers = std::map<std::string, Texturer*>();

TextDrawer::TextDrawer(Renderer * parent, std::string fontPath)
	:Drawer(parent),m_FontFilePath(fontPath)
{
	this->m_Shaderer = new Shaderer("TextShader.shader");
	glm::mat4 projection = glm::mat4(1.0f);
	this->m_Shaderer->Bind();
	this->m_Shaderer->SetUniformMat4f("projection", projection);
	this->m_Shaderer->Unbind();
	this->LoadFont();

	this->m_Text = (char*)malloc(2);
	memset(this->m_Text, 0, 2);
	*this->m_Text = 'O';


#pragma region 创建字符绘制的顶点对象
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
#pragma endregion


#pragma region 创建矩形框的顶点对象
	float vertices[] =
	{
		-0.5f,-0.5f,0.0f,0.0f,
		-0.5f,0.5f,0.0f,0.0f,
		0.5f,0.5f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,0.0f
	};
	this->m_RectVBO = new VertexBuffer(vertices, sizeof(vertices));
	this->m_RectVAO = new VertexArray(this->m_RectVBO);
	this->m_RectVAO->AddVertexAttrib(new VertexAttrib(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0));
#pragma endregion
}

TextDrawer::~TextDrawer()
{
}

void TextDrawer::Draw()
{
	//const char text[] = { 0xE4, 0xB8, 0xAD,0x0 };
	const char text[] = "O";
	//this->DrawText(text, 0.5f, 0.5f, 65.0f);
	this->DrawText(this->m_Text, 0.5f, 0.5f, 65.0f);
	//this->DrawRect();
}

void TextDrawer::ProcessInput(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		*this->m_Text = 'A';
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
	{
		*this->m_Text = 'B';
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		*this->m_Text = 'C';
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		*this->m_Text = 'D';
	}
}

void TextDrawer::LoadFont()
{

	unsigned char* fontBuffer;
	int fontWidth = 512;
	int fontHeight = 512;
	FILE* fontFile = fopen(this->m_FontFilePath.c_str(), "rb");
	fseek(fontFile, 0, SEEK_END);
	long fileSize = ftell(fontFile);
	fseek(fontFile, 0, SEEK_SET);

	fontBuffer = (unsigned char*)malloc(fileSize);
	fread(fontBuffer, 1, fileSize, fontFile);
	fclose(fontFile);

	stbtt_InitFont(&font, fontBuffer, stbtt_GetFontOffsetForIndex(fontBuffer, 0));

	//this->InitTexturers();

}

void TextDrawer::InitTexturers()
{
	float size = 65.0f;
	float scale = stbtt_ScaleForPixelHeight(&font, size);
	int ascent, descent, lineGap;
	stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
	ascent *= scale;
	descent *= scale;
	int glyphIndex;

	for (int i = 0; i < 128; i++)
	{
		glyphIndex = stbtt_FindGlyphIndex(&font, i);
		int advance, lsb;
		stbtt_GetGlyphHMetrics(&font, glyphIndex, &advance, &lsb);

		int x0, y0, x1, y1;
		stbtt_GetGlyphBitmapBox(&font, glyphIndex, scale, scale, &x0, &y0, &x1, &y1);
		int width = x1 - x0;
		int height = y1 - y0;
		unsigned char* bitmap = (unsigned char*)malloc(width * height);
		stbtt_MakeGlyphBitmap(&font, bitmap, width, height, width, scale, scale, glyphIndex);
		
		//bitmap数据Y轴翻转
		for (int row = 0; row < height / 2; ++row)
		{
			for (int col = 0; col < width; ++col)
			{
				std::swap(bitmap[row * width + col], bitmap[(height - 1 - row) * width + col]);
			}
		}
		//stbi_write_png("STB.png", width, height, 1, bitmap, width);
		std::string str = std::to_string(i);
		Texturer* texturer = new Texturer(bitmap, width, height);
		TextDrawer::m_TextTexturers.insert(std::pair<std::string, Texturer*>(str, texturer));
		
		free(bitmap);
	}

}

void TextDrawer::DrawText(const char * text, float x, float y, float size)
{

	



	
	while (*text) 
	{


#pragma region 动态给顶点赋值数据
		// update VBO for each character
		//float vertices[6][4] = {
		//	{ xpos,     ypos + h,   0.0f, 0.0f },
		//	{ xpos,     ypos,       0.0f, 1.0f },
		//	{ xpos + w, ypos,       1.0f, 1.0f },

		//	{ xpos,     ypos + h,   0.0f, 0.0f },
		//	{ xpos + w, ypos,       1.0f, 1.0f },
		//	{ xpos + w, ypos + h,   1.0f, 0.0f }
		//};
		//float vertices[6][4] =
		//{
		//{0.5f,  0.5f,1.0f, 1.0f},//0
		//{0.5f, 0.45f,1.0f,0.0f},//1
		//{0.45f,  0.5f,0.0f,1.0f},//3
		//{0.5f, 0.45f,1.0f,0.0f},//1
		//{0.45f, 0.45f,0.0f,0.0f},//2
		//{0.45f,  0.5f,0.0f,1.0f}//3
		//};
		float vertices[6][4]=
		{
		{0.5f,  0.5f,1.0f, 1.0f},//0
		{0.5f, -0.5f,1.0f,0.0f},//1
		{-0.5f,  0.5f,0.0f,1.0f},//3
		{0.5f, -0.5f,1.0f,0.0f},//1
		{-0.5f, -0.5f,0.0f,0.0f},//2
		{-0.5f,  0.5f,0.0f,1.0f}//3
		};

		// render glyph texture over quad
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		this->m_Shaderer->Bind();
		std::string ch = std::to_string(*text);
		int slot = 3;
		this->FindCharTexturer(ch)->Bind(slot);
		this->m_Shaderer->SetUniform1i("text", slot);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(VAO);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glPointSize(5.0f);
		glDrawArrays(GL_POINTS, 0, 6);
		this->m_Shaderer->Unbind();
#pragma endregion



		text++;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextDrawer::DrawRect()
{
	this->m_Shaderer->Bind();
	this->m_RectVAO->Bind();
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glPointSize(15.0f);
	glDrawArrays(GL_POINTS, 0, 6);
	this->m_RectVAO->Unbind();
	this->m_Shaderer->Unbind();
}

Texturer * TextDrawer::FindCharTexturer(std::string ch)
{
	if (this->m_TextTexturers.find(ch) == this->m_TextTexturers.end())
	{
		float size = 65.0f;
		float scale = stbtt_ScaleForPixelHeight(&font, size);
		int ascent, descent, lineGap;
		stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
		ascent *= scale;
		descent *= scale;
		int glyphIndex;
		int codepoint = this->UTF8ToUnicode(ch.c_str(), strlen(ch.c_str()));
		glyphIndex = stbtt_FindGlyphIndex(&font, codepoint);
		int advance, lsb;
		stbtt_GetGlyphHMetrics(&font, glyphIndex, &advance, &lsb);

		int x0, y0, x1, y1;
		stbtt_GetGlyphBitmapBox(&font, glyphIndex, scale, scale, &x0, &y0, &x1, &y1);
		int width = x1 - x0;
		int height = y1 - y0;
		unsigned char* bitmap = (unsigned char*)malloc(width * height);
		stbtt_MakeGlyphBitmap(&font, bitmap, width, height, width, scale, scale, glyphIndex);

		//bitmap数据Y轴翻转
		for (int row = 0; row < height / 2; ++row)
		{
			for (int col = 0; col < width; ++col)
			{
				std::swap(bitmap[row * width + col], bitmap[(height - 1 - row) * width + col]);
			}
		}
		//stbi_write_png("STB.png", width, height, 1, bitmap, width);
		Texturer* texturer = new Texturer(bitmap, width, height);
		TextDrawer::m_TextTexturers.insert(std::pair<std::string, Texturer*>(ch, texturer));
		free(bitmap);
	}
	else
	{
		return this->m_TextTexturers[ch];
	}
}


//输入一个字符的所有字节,返回对应的码点
int TextDrawer::UTF8ToUnicode(const char * utf8, int length)
{
	int unicode = 0;
	int i = 0;

	if ((utf8[0] & 0x80) == 0) 
	{
		// Single-byte character
		unicode = utf8[0];
	}
	else if ((utf8[0] & 0xE0) == 0xC0) 
	{
		// Two-byte character
		unicode = (utf8[0] & 0x1F) << 6;
		unicode |= (utf8[1] & 0x3F);
	}
	else if ((utf8[0] & 0xF0) == 0xE0) 
	{
		// Three-byte character
		unicode = (utf8[0] & 0x0F) << 12;
		unicode |= (utf8[1] & 0x3F) << 6;
		unicode |= (utf8[2] & 0x3F);
	}
	else if ((utf8[0] & 0xF8) == 0xF0) 
	{
		// Four-byte character
		unicode = (utf8[0] & 0x07) << 18;
		unicode |= (utf8[1] & 0x3F) << 12;
		unicode |= (utf8[2] & 0x3F) << 6;
		unicode |= (utf8[3] & 0x3F);
	}

	return unicode;
}
