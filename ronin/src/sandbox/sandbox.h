#pragma once
#include "roninpch.h"

#include <glm/glm.hpp>

#include "core/layer.h"
#include "core/timestep.h"
#include "core/openGL/vertex-buffer.h"
#include "shader/shader.h"
#include "voxel/chunck.h"
#include "sandbox/camera.h"
#include "sandbox/renderer.h"

class SandBox : public Layer {
public:

private:
	Shader* mainShader;
	VertexBuffer* vb;
	Renderer* renderer;

	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	glm::mat4 modelMatrix = glm::mat4(1.0f);


	bool firstMouse = true;
	Timestep dt;

	Chunk chunk;
	GLFWwindow* window;

	// ? Some settings for debug
	bool isProjectionInPerspective = true;
	bool isViewInWireframe = false;

public:
	SandBox();
	SandBox(GLFWwindow* window);
	virtual ~SandBox();
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(Timestep timeStep) override;
	virtual void onEvent(GLFWwindow* window, Timestep timeStep) override;
	virtual void onImGui(ImGuiIO& io, Timestep timeStep) override;

	void updateBufferColor();
	void framebuffer_size_callback();
};
