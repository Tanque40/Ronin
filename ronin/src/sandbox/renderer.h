#pragma once
#include "roninpch.h"

#include <glm/glm.hpp>

#include "shader/shader.h"
#include "sandbox/globals.h"
#include "core/openGL/vertex-buffer.h"

class Renderer {
private:
	Shader* mainShader;
	VertexBuffer* vb;
	std::vector<unsigned int> indices;
	unsigned int VAO, EBO;

public:
	Renderer(VertexBuffer* _vb, Shader* _mainShader);
	~Renderer();

	virtual void start();
	virtual void draw(glm::mat4 projectionMatrix, glm::mat4 modelMatrix);
};
