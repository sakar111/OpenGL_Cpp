#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"
#include"Light.h"
#include "Material.h"


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	//Set Uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, const glm::vec3& vector);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat3f(const std::string& name, const glm::mat3& matrix);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniformMaterial(const std::string& name, const Material& material);
	void SetUniformLight(const std::string& name, const Light& light);
	//void SetUniformLightingMap(const std::string& name, const LightingMap& lightingMap);

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int GetUniformLocation(const std::string& name);
};