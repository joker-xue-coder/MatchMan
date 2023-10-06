#pragma once
#include "Common.h"
#include "stb_image.h"
typedef struct TexturerParameter
{
	GLenum target; //纹理类型
	GLenum pname;  //参数名称
	GLint param;   //参数值
	TexturerParameter(GLenum pname, GLint param, GLenum target = GL_TEXTURE_2D)
		:pname(pname), param(param), target(target)
	{

	}
	TexturerParameter() {};
}TexturerParameter;
class Texturer
{
public:
	Texturer(std::string imagePath, std::map<int, TexturerParameter> texturerParas = std::map<int, TexturerParameter>(), bool reverseY = true);
	Texturer(unsigned char* data, int width, int height, std::map<int, TexturerParameter> texturerParas = std::map<int, TexturerParameter>());
	~Texturer();

	void Bind(unsigned int  slot = 0)const;
	void Unbind()const;

	inline int GetWidth()const { return this->m_Width; }
	inline int GetHeight()const { return this->m_Height; }
	inline int GetChannels()const { return this->m_Channels; }
	//inline unsigned int GetTexturerID()const { return this->m_TexturerID; }
private:
	void InitTexturerParameters(std::map<int, TexturerParameter> texturerParas);
private:
	unsigned int m_TexturerID;
	int m_Width;
	int m_Height;
	int m_Channels;
	std::map<int, TexturerParameter> m_TexturerParas;
};

