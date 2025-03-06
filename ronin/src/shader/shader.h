#pragma once

#include "roninpch.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSource {
	std::string vertexSource;
	std::string fragmentSource;
	std::string geometrySource;
};

class Shader {
private:
	unsigned int rendererId;
	std::unordered_map<std::string, int> uniformLocationCache;
	ShaderProgramSource shaders;

public:
	inline Shader() {};
	Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath);
	Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath, const std::string& geometryFilePath);
	~Shader();

	void bind() const;
	void unBind() const;

	// set uniforms
	void SetUniform1i(const std::string& name, int value);
	void SetUniform4f(const std::string& name, glm::vec4 vector);
	void SetUniformsMat4f(const std::string& name, const glm::mat4& mat4);

private:
	std::string parseShader(const std::string& filepath);
	unsigned int compileShader(unsigned int type, const std::string& source);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader);
	int getUniformLocation(const std::string& name);
};
