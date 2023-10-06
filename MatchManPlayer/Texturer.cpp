#include "Texturer.h"

Texturer::Texturer(std::string imagePath, std::map<int, TexturerParameter> texturerParas,bool reverseY)
{
	this->InitTexturerParameters(texturerParas);

	glGenTextures(1, &this->m_TexturerID);
	glBindTexture(GL_TEXTURE_2D, this->m_TexturerID);

	for (std::map<int, TexturerParameter>::iterator it = texturerParas.begin(); it != texturerParas.end(); it++)
	{
		glTexParameteri(it->second.target, it->second.pname, it->second.param);
	}
	if (reverseY)
	{
		stbi_set_flip_vertically_on_load(1);
	}
	unsigned char *data = stbi_load(imagePath.c_str(), &this->m_Width, &this->m_Height, &this->m_Channels, 0);//STBI_rgb_alpha
	if (data)
	{
		//4通道数据可以使用3通道数据来读取,只是数据会错乱.
		//3通道数据不可以使用4通道来读取,会导致内存越界.
		if (this->m_Channels == 3)
		{
			//3通道的话就对应GL_RGB
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_Width, this->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (this->m_Channels == 4)
		{
			//4通道的话就对应GL_RGBA
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->m_Width, this->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else
	{
		PrintLog("Failed to load texture");
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

//目前主要针对字体的加载
Texturer::Texturer(unsigned char * data, int width, int height, std::map<int, TexturerParameter> texturerParas)
	:m_Width(width),m_Height(height)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &this->m_TexturerID);
	glBindTexture(GL_TEXTURE_2D, this->m_TexturerID);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RED,
		this->m_Width,
		this->m_Height,
		0,
		GL_RED,
		GL_UNSIGNED_BYTE,
		data
	);
	// set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texturer::~Texturer()
{
	glDeleteTextures(1, &this->m_TexturerID);
}

void Texturer::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, this->m_TexturerID);
}

void Texturer::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texturer::InitTexturerParameters(std::map<int, TexturerParameter> texturerParas)
{
	//分别先设置四个参数的默认值
	//环绕方式
	/*
	GL_REPEAT	对纹理的默认行为。重复纹理图像。
	GL_MIRRORED_REPEAT	和GL_REPEAT一样，但每次重复图片是镜像放置的。
	GL_CLAMP_TO_EDGE	纹理坐标会被约束在0到1之间，超出的部分会重复纹理坐标的边缘，产生一种边缘被拉伸的效果。
	GL_CLAMP_TO_BORDER	超出的坐标为用户指定的边缘颜色。
	*/
	//GL_TEXTURE_WRAP_S水平方向上的环绕方式
	this->m_TexturerParas.insert(std::pair<int, TexturerParameter>(GL_TEXTURE_WRAP_S, TexturerParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)));
	//GL_TEXTURE_WRAP_T竖直方向上的环绕方式
	this->m_TexturerParas[GL_TEXTURE_WRAP_T] = TexturerParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	//过滤方式
	/*
	GL_NEAREST（也叫邻近过滤，Nearest Neighbor Filtering）是OpenGL默认的纹理过滤方式。
	GL_LINEAR（也叫线性过滤，(Bi)linear Filtering）它会基于纹理坐标附近的纹理像素，计算出一个插值，近似出这些纹理像素之间的颜色。
	*/

	/*
	针对缩小有用的多级渐远纹理
	GL_NEAREST_MIPMAP_NEAREST	使用最邻近的多级渐远纹理来匹配像素大小，并使用邻近插值进行纹理采样
	GL_LINEAR_MIPMAP_NEAREST	使用最邻近的多级渐远纹理级别，并使用线性插值进行采样
	GL_NEAREST_MIPMAP_LINEAR	在两个最匹配像素大小的多级渐远纹理之间进行线性插值，使用邻近插值进行采样
	GL_LINEAR_MIPMAP_LINEAR	在两个邻近的多级渐远纹理之间使用线性插值，并使用线性插值进行采样
	*/
	//GL_TEXTURE_MIN_FILTER缩小过滤方式
	this->m_TexturerParas[GL_TEXTURE_MIN_FILTER] = TexturerParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//GL_TEXTURE_MAG_FILTER放大过滤方式
	this->m_TexturerParas[GL_TEXTURE_MAG_FILTER] = TexturerParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	for (std::map<int, TexturerParameter>::iterator it = texturerParas.begin(); it != texturerParas.end(); it++)
	{
		this->m_TexturerParas[it->first] = it->second;
	}

}
