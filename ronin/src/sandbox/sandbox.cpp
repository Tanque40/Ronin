#include "sandbox/sandbox.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include "sandbox/globals.h"

float lastX = 1920 / 2.0f;
float lastY = 1080 / 2.0f;

SandBox::SandBox() {}

SandBox::SandBox(GLFWwindow* _window) : window(_window) {
}

SandBox::~SandBox() {
}

void SandBox::onAttach() {
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		// make sure the viewport matches the new window dimensions; note that width and
		// height will be significantly larger than specified on retina displays.
		SandBoxGlobals::width = width;
		SandBoxGlobals::height = height;
		SandBoxGlobals::idViewPortChanged = true;
		glViewport(0, 0, width, height);
		});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		SandBoxGlobals::camera.ProcessMouseMovement(xoffset, yoffset);
		});
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		SandBoxGlobals::camera.Zoom -= (float)yoffset / 4;
		if (SandBoxGlobals::camera.Zoom < 1.0f)
			SandBoxGlobals::camera.Zoom = 1.0f;
		if (SandBoxGlobals::camera.Zoom > 50.0f)
			SandBoxGlobals::camera.Zoom = 50.0f;
		SandBoxGlobals::camera.ProcessMouseScroll(yoffset);
		});

	float* data = voxel.getVertexData();

	// build and compile our shader program
	// ------------------------------------
	mainShader = new Shader("res/shaders/initial.vs.glsl", "res/shaders/initial.fs.glsl");
	renderer = new Renderer(mainShader, data);
	renderer->start();

	if (isProjectionInPerspective) {
		projectionMatrix = glm::perspective(glm::radians(60.0f), (float)SandBoxGlobals::width / (float)SandBoxGlobals::height, 0.1f, 90.0f);
	}
	else {
		projectionMatrix = glm::ortho(
			(float)SandBoxGlobals::width / -1.0f,
			(float)SandBoxGlobals::height / 1.0f,
			(float)SandBoxGlobals::width / -1.0f,
			(float)SandBoxGlobals::height / 1.0f,
			-10.0f,
			10.0f
		);
	}

	// note that we're translating the scene in the reverse direction of where we want to move
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
	spdlog::info("Ronin running");

}

void SandBox::onDetach() {
	delete renderer;
}

void SandBox::onUpdate(Timestep timeStep) {
	if (SandBoxGlobals::idViewPortChanged) {
		framebuffer_size_callback();
	}
	if (isViewInWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	onEvent(window, timeStep);

	renderer->draw(projectionMatrix, modelMatrix);
}

void SandBox::onEvent(GLFWwindow* window, Timestep timeStep) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		SandBoxGlobals::camera.ProcessKeyboard(Camera_Movement::FORWARD, float(timeStep) * 10);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		SandBoxGlobals::camera.ProcessKeyboard(Camera_Movement::LEFT, float(timeStep) * 10);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		SandBoxGlobals::camera.ProcessKeyboard(Camera_Movement::RIGHT, float(timeStep) * 10);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		SandBoxGlobals::camera.ProcessKeyboard(Camera_Movement::BACKWARD, float(timeStep) * 10);
	}

	// ! Close window and program
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void SandBox::onImGui(ImGuiIO& io, Timestep timeStep) {
	ImGui::Begin("Ronin project");
	ImGui::Text("Starter menu for Ronin project.");
	ImGui::Text("Thesis project to obtain a computer engeneer degree.");
	if (ImGui::ColorEdit4("clear color", voxel.getVoxelColor())) {
		updateBufferColor();
	}

	if (ImGui::Checkbox("Projection in perspective", &isProjectionInPerspective)) {
		framebuffer_size_callback();
	}
	ImGui::Checkbox("Wireframe View", &isViewInWireframe);
	ImGui::Text("Application \n average %.3f ms/frame \n(%.1f FPS)", timeStep.getMilliseconds(), io.Framerate);
	ImGui::End();
}

void SandBox::updateBufferColor() {
	float* data = voxel.getVertexData();

	glBufferData(GL_ARRAY_BUFFER, 24 * 6 * sizeof(float), data, GL_DYNAMIC_DRAW);
}

void SandBox::framebuffer_size_callback() {
	SandBoxGlobals::idViewPortChanged = false;
	if (isProjectionInPerspective) {
		projectionMatrix = glm::perspective(glm::radians(60.0f), (float)SandBoxGlobals::width / (float)SandBoxGlobals::height, 0.1f, 90.0f);
		modelMatrix = glm::scale(modelMatrix, glm::vec3((1 / 10.0f)));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
	}
	else {
		projectionMatrix = glm::ortho(
			(float)SandBoxGlobals::width / -5.0f,
			(float)SandBoxGlobals::height / 5.0f,
			(float)SandBoxGlobals::width / -5.0f,
			(float)SandBoxGlobals::height / 5.0f,
			-100.0f,
			100.0f
		);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(10.0f));
	}
}
