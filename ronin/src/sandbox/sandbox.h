#include "roninpch.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

#include "core/layer.h"
#include "shader/shader.h"
#include "voxel/voxel.h"
#include "sandbox/camera.h"

class SandBox : public Layer {
private:
	// settings
	static const unsigned int SCR_WIDTH = 1280;
	static const unsigned int SCR_HEIGHT = 960;
	Shader* mainShader;
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 90.0f);
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

	Voxel voxel;
public:
	SandBox();
	virtual ~SandBox();
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate() override;
	virtual void onEvent() override;
	virtual void onImGui( ImGuiIO& io ) override;
	void updateBufferColor();
};
