#include "Shaderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Shaderer::Shaderer(const std::string & filepath)
	:m_FilePath(filepath),m_ShadererProgramID(0)
{
	//通过文件获取shader源码;
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
	//通过统一变量名称获取已经创建成功的shader中的变量指针
	//每次先从表中查找是否记录过该统一变量的值
	if (this->m_UniformLocationCache.find(name) != this->m_UniformLocationCache.end())
	{
		return this->m_UniformLocationCache[name];
	}


	int location = glGetUniformLocation(this->m_ShadererProgramID, name.c_str());
	if (location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}
	//添加统一变量的值
	this->m_UniformLocationCache[name] = location;

	return location;
}

unsigned int Shaderer::CompileShader(unsigned int type, const std::string & source)
{
	//通过shader类型创建一个shader并且返回shader的ID
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	//通过id绑定shader的内容
	glShaderSource(id, 1, &src, nullptr);

	//编译一个shader
	glCompileShader(id);

	//着色器编译是否成功的结果
	int result;
	//检测着色器是否编译成功
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE) 
	{
		int length;
		//获取着色器编译失败的原因
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(sizeof(char)*length);
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		//如果着色器编译失败的话释放着色器的id
		glDeleteShader(id);
		return 0;
	}
	//返回一个编译成功的着色器id
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
	unsigned int program = glCreateProgram();//创建一个着色器项目,并且返回项目id,可以绑定多个着色器
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);//顶点着色器也就是画边使用的
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);//片段着色器也就是填充使用的
	//将着色器绑定到这个项目上面
	/*
	使着色器关联项目
	param1:着色器项目id
	param2:着色器id
	*/
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	//连接一个项目
	glLinkProgram(program);
	//检验项目的有效性
	glValidateProgram(program);
	//项目敲定之后释放着色器
	glDeleteShader(vs);
	//glDeleteShader(fs);
	//返回一个着色器项目
	return program;
}
