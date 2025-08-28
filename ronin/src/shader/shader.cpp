#include "roninpch.h"

#include "shader/shader.h"

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath) : rendererId(0) {
	ShaderProgramSource source = { parseShader(vertexFilePath), parseShader(fragmentFilePath), "" };
	rendererId = createShader(source.vertexSource, source.fragmentSource);
}

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath, const std::string& geometryFilePath) : rendererId(0) {
	ShaderProgramSource source = { parseShader(vertexFilePath), parseShader(fragmentFilePath), parseShader(geometryFilePath) };
	rendererId = createShader(source.vertexSource, source.fragmentSource, source.geometrySource);
}

Shader::~Shader() {
	glDeleteProgram(rendererId);
}

void Shader::bind() const {
	glUseProgram(rendererId);
}

void Shader::unBind() const {
	glUseProgram(0);
}

// * Uniforms

void Shader::SetUniform1i(const std::string& name, int value) {
	glUniform1i(getUniformLocation(name), value);
}

void Shader::SetUniformsMat4f(const std::string& name, const glm::mat4& mat4) {
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat4[0][0]);
}

void Shader::SetUniformsVec3f(const std::string& name, const glm::vec3& vec3) {
	glUniform3fv(getUniformLocation(name), 1, &vec3[0]);
}

void Shader::SetUniformsVec4f(const std::string& name, const glm::vec4& vec4) {
	glUniform4fv(getUniformLocation(name), 1, &vec4[0]);
}

// * Utils

std::string Shader::parseShader(const std::string& filepath) {
#ifdef __APPLE__
	std::fstream stream("ronin/" + filepath);
#else
	std::fstream stream(filepath);
#endif
	std::string line, ss;

	while (getline(stream, line)) {
		ss += line += '\n';
	}

	return ss;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {

		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile Shader" << (type == GL_VERTEX_SHADER ? "vertex" : type == GL_FRAGMENT_SHADER ? "fragment" : "geometry") << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;

	}

	return id;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader, const std::string& geometryShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	unsigned int gs = compileShader(GL_GEOMETRY_SHADER, geometryShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glAttachShader(program, gs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(gs);

	return program;
}

int Shader::getUniformLocation(const std::string& name) {
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache[name];

	int location = glGetUniformLocation(rendererId, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exists!" << std::endl;

	uniformLocationCache[name] = location;
	return location;
}
