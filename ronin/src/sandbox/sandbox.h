#pragma once
#include "roninpch.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#include "core/layer.h"
#include "core/timestep.h"
#include "shader/shader.h"
#include "voxel/voxel.h"
#include "sandbox/camera.h"

class SandBox : public Layer {
private:
	// settings
	static unsigned int width, height;
	static bool idViewPortChanged;
	Shader* mainShader;
	glm::mat4 projectionMatrix = glm::mat4(1.0f);
	//glm::mat4 projectionMatrix = glm::ortho(
	//	(float)SCR_WIDTH / -2.0f,
	//	(float)SCR_WIDTH / 2.0f,
	//	(float)SCR_HEIGHT / -2.0f,
	//	(float)SCR_HEIGHT / 2.0f,
	//	-10.0f,
	//	10.0f
	//);
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	Camera camera;
	glm::mat4 modelMatrix = glm::mat4(1.0f);
	unsigned int VBO, VAO, EBO;
	bool firstMouse = true;
	Timestep dt;

	Voxel voxel;
	GLFWwindow* window;
public:
	SandBox();
	SandBox(GLFWwindow* window);
	virtual ~SandBox();
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(Timestep timeStep) override;
	virtual void onEvent(GLFWwindow* window) override;
	virtual void onImGui(ImGuiIO& io, Timestep timeStep) override;

	void updateBufferColor();
	void framebuffer_size_callback();
};
