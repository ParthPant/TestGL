#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader 
{
private:
	unsigned int m_RendererID;
	std::string m_filePath;
	std::unordered_map<std::string, unsigned int> m_UniformLocationCache;

	int getUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderSource ParseShader(const std::string& file);
public:
	Shader(const std::string& file);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void setUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
	void setUniform1i(const std::string& name, int value);
	void setUniformMat4f(const std::string& name, glm::mat4& matrix);
};