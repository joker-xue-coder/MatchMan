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
		//4ͨ�����ݿ���ʹ��3ͨ����������ȡ,ֻ�����ݻ����.
		//3ͨ�����ݲ�����ʹ��4ͨ������ȡ,�ᵼ���ڴ�Խ��.
		if (this->m_Channels == 3)
		{
			//3ͨ���Ļ��Ͷ�ӦGL_RGB
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_Width, this->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else if (this->m_Channels == 4)
		{
			//4ͨ���Ļ��Ͷ�ӦGL_RGBA
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

//Ŀǰ��Ҫ�������ļ���
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
	//�ֱ��������ĸ�������Ĭ��ֵ
	//���Ʒ�ʽ
	/*
	GL_REPEAT	�������Ĭ����Ϊ���ظ�����ͼ��
	GL_MIRRORED_REPEAT	��GL_REPEATһ������ÿ���ظ�ͼƬ�Ǿ�����õġ�
	GL_CLAMP_TO_EDGE	��������ᱻԼ����0��1֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч����
	GL_CLAMP_TO_BORDER	����������Ϊ�û�ָ���ı�Ե��ɫ��
	*/
	//GL_TEXTURE_WRAP_Sˮƽ�����ϵĻ��Ʒ�ʽ
	this->m_TexturerParas.insert(std::pair<int, TexturerParameter>(GL_TEXTURE_WRAP_S, TexturerParameter(GL_TEXTURE_WRAP_S, GL_REPEAT)));
	//GL_TEXTURE_WRAP_T��ֱ�����ϵĻ��Ʒ�ʽ
	this->m_TexturerParas[GL_TEXTURE_WRAP_T] = TexturerParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	//���˷�ʽ
	/*
	GL_NEAREST��Ҳ���ڽ����ˣ�Nearest Neighbor Filtering����OpenGLĬ�ϵ�������˷�ʽ��
	GL_LINEAR��Ҳ�����Թ��ˣ�(Bi)linear Filtering����������������긽�����������أ������һ����ֵ�����Ƴ���Щ��������֮�����ɫ��
	*/

	/*
	�����С���õĶ༶��Զ����
	GL_NEAREST_MIPMAP_NEAREST	ʹ�����ڽ��Ķ༶��Զ������ƥ�����ش�С����ʹ���ڽ���ֵ�����������
	GL_LINEAR_MIPMAP_NEAREST	ʹ�����ڽ��Ķ༶��Զ�����𣬲�ʹ�����Բ�ֵ���в���
	GL_NEAREST_MIPMAP_LINEAR	��������ƥ�����ش�С�Ķ༶��Զ����֮��������Բ�ֵ��ʹ���ڽ���ֵ���в���
	GL_LINEAR_MIPMAP_LINEAR	�������ڽ��Ķ༶��Զ����֮��ʹ�����Բ�ֵ����ʹ�����Բ�ֵ���в���
	*/
	//GL_TEXTURE_MIN_FILTER��С���˷�ʽ
	this->m_TexturerParas[GL_TEXTURE_MIN_FILTER] = TexturerParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//GL_TEXTURE_MAG_FILTER�Ŵ���˷�ʽ
	this->m_TexturerParas[GL_TEXTURE_MAG_FILTER] = TexturerParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);


	for (std::map<int, TexturerParameter>::iterator it = texturerParas.begin(); it != texturerParas.end(); it++)
	{
		this->m_TexturerParas[it->first] = it->second;
	}

}
