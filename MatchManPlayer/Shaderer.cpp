#include "Shaderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shaderer::Shaderer(const std::string & filepath)
	:m_FilePath(filepath),m_ShadererProgramID(0)
{
	//ͨ���ļ���ȡshaderԴ��;
	ShadererProgramSource source = ParseShader(filepath);
	this->m_ShadererProgramID = CreateShader(source.VertexSource, source.FragmentSource);

}

Shaderer::~Shaderer()
{
	glDeleteProgram(this->m_ShadererProgramID);
}

void Shaderer::Bind() const
{
	glUseProgram(this->m_ShadererProgramID);
}

void Shaderer::Unbind() const
{
	glUseProgram(0);
}

void Shaderer::SetUniform4f(const std::string & name, float f0, float f1, float f2, float f3)
{
	glUniform4f(this->GetUniformLocation(name), f0, f1, f2, f3);
}

void Shaderer::SetUniform1f(const std::string & name, float value)
{
	glUniform1f(this->GetUniformLocation(name), value);
}

void Shaderer::SetUniform1i(const std::string & name, int value)
{
	glUniform1i(this->GetUniformLocation(name), value);
}

void Shaderer::SetUniformMat4f(const std::string & name, glm::mat4 matrix)
{
	glUniformMatrix4fv(this->GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shaderer::GetUniformLocation(const std::string & name)
{
	//ͨ��ͳһ�������ƻ�ȡ�Ѿ������ɹ���shader�еı���ָ��
	//ÿ���ȴӱ��в����Ƿ��¼����ͳһ������ֵ
	if (this->m_UniformLocationCache.find(name) != this->m_UniformLocationCache.end())
	{
		return this->m_UniformLocationCache[name];
	}


	int location = glGetUniformLocation(this->m_ShadererProgramID, name.c_str());
	if (location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}
	//���ͳһ������ֵ
	this->m_UniformLocationCache[name] = location;

	return location;
}

unsigned int Shaderer::CompileShader(unsigned int type, const std::string & source)
{
	//ͨ��shader���ʹ���һ��shader���ҷ���shader��ID
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	//ͨ��id��shader������
	glShaderSource(id, 1, &src, nullptr);

	//����һ��shader
	glCompileShader(id);

	//��ɫ�������Ƿ�ɹ��Ľ��
	int result;
	//�����ɫ���Ƿ����ɹ�
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) 
	{
		int length;
		//��ȡ��ɫ������ʧ�ܵ�ԭ��
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(sizeof(char)*length);
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		//�����ɫ������ʧ�ܵĻ��ͷ���ɫ����id
		glDeleteShader(id);
		return 0;
	}
	//����һ������ɹ�����ɫ��id
	return id;
}

ShadererProgramSource Shaderer::ParseShader(const std::string & filepath)
{
	std::ifstream stream(filepath);
	enum class ShaderType 
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("shader") != std::string::npos) 
		{
			if (line.find("vertex") != std::string::npos) 
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) 
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else 
		{
			//std::cout << line << std::endl;
			ss[(int)type] << line << '\n';
		}
	}
	return{ ss[0].str(), ss[1].str() };

}

unsigned int Shaderer::CreateShader(const std::string & vertexShader, const std::string & fragmentShader)
{
	unsigned int program = glCreateProgram();//����һ����ɫ����Ŀ,���ҷ�����Ŀid,���԰󶨶����ɫ��
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);//������ɫ��Ҳ���ǻ���ʹ�õ�
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);//Ƭ����ɫ��Ҳ�������ʹ�õ�
	//����ɫ���󶨵������Ŀ����
	/*
	ʹ��ɫ��������Ŀ
	param1:��ɫ����Ŀid
	param2:��ɫ��id
	*/
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	//����һ����Ŀ
	glLinkProgram(program);
	//������Ŀ����Ч��
	glValidateProgram(program);
	//��Ŀ�ö�֮���ͷ���ɫ��
	glDeleteShader(vs);
	//glDeleteShader(fs);
	//����һ����ɫ����Ŀ
	return program;
}
