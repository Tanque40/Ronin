#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "shader/shader.h"
#include "sandbox/globals.h"

class Renderer {
private:
	Shader* mainShader;
	float* data;
	unsigned int VBO, VAO, EBO;

public:
	Renderer(Shader* _mainShader, float* _data);
	~Renderer();

	virtual void start();
	virtual void draw(glm::mat4 projectionMatrix, glm::mat4 modelMatrix);
};
