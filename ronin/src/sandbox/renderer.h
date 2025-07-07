#pragma once
#include "roninpch.h"

#include <glm/glm.hpp>

#include "shader/shader.h"
#include "sandbox/globals.h"

class Renderer {
private:
	Shader* mainShader;
	std::vector<float>* data;
	std::vector<unsigned int> indices;
	unsigned int VBO, VAO, EBO;

public:
	Renderer(Shader* _mainShader, std::vector<float>* _data);
	~Renderer();

	virtual void start();
	virtual void draw(glm::mat4 projectionMatrix, glm::mat4 modelMatrix);
};
