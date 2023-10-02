#pragma once

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <glm.hpp>


struct ShadererProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shaderer
{
public:
	Shaderer(const std::string& filepath);
	~Shaderer();

	void Bind()const;
	void Unbind()const;

	//Set Uniform
	void SetUniform4f(const std::string& name, float f0, float f1, float f2, float f3);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform1i(const std::string& name, int value);

	void SetUniformMat4f(const std::string& name, glm::mat4 matrix);
private:
	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	ShadererProgramSource ParseShader(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

private:
	std::string m_FilePath;
	unsigned int m_ShadererProgramID;
	//caching for uniform,建立一个统一变量的指针表,不需要每次都从shader中\
	获取location,每次通过名称从表中获取统一变量的location
	std::unordered_map<std::string, int> m_UniformLocationCache;

};

