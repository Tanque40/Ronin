#include "roninpch.h"

#include "sandbox/sandbox.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#include "sandbox/globals.h"

float lastX = SandBoxGlobals::width / 2.0f;
float lastY = SandBoxGlobals::height / 2.0f;

SandBox::SandBox() {}

SandBox::SandBox(GLFWwindow* _window) : window(_window) {
}

SandBox::~SandBox() {
}

void SandBox::onAttach() {
	spdlog::info("SandBox running");
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		// make sure the viewport matches the new window dimensions; note that width and
		// height will be significantly larger than specified on retina displays.
		SandBoxGlobals::width = width;
		SandBoxGlobals::height = height;
		SandBoxGlobals::idViewPortChanged = true;
		glViewport(0, 0, width, height);
		});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		if (SandBoxGlobals::fistMouse) {
			lastX = xpos;
			lastY = ypos;
			SandBoxGlobals::fistMouse = false;
		}
		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		SandBoxGlobals::camera.ProcessMouseMovement(xoffset, yoffset);
		});
	glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
		//spdlog::info("Mouse scroll: xoffset: {}, yoffset: {}", xoffset, yoffset);
		SandBoxGlobals::camera.ProcessMouseScroll(yoffset);
		});


	chunk = Chunk(25);
	chunk.generateChunk();
	std::vector<float>* data = chunk.getData();
	vb = new VertexBuffer();
	vb->setData(data->data(), data->size() * sizeof(float));

	// build and compile our shader program
	// ------------------------------------
	mainShader = new Shader("res/shaders/initial.vs.glsl", "res/shaders/initial.fs.glsl");
	renderer = new Renderer(vb, mainShader);
	renderer->start();

	if (isProjectionInPerspective) {
		projectionMatrix = glm::perspective(glm::radians(SandBoxGlobals::camera.Zoom), (float)SandBoxGlobals::width / (float)SandBoxGlobals::height, 0.1f, 200.0f);
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

	//modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));

	spdlog::info("Voxels matrix:\n{}", chunk.toString());
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
	projectionMatrix = glm::perspective(glm::radians(SandBoxGlobals::camera.Zoom), (float)SandBoxGlobals::width / (float)SandBoxGlobals::height, 0.1f, 100.0f);

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

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		if (SandBoxGlobals::isOnMenu) {
			SandBoxGlobals::isOnMenu = false;

			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			SandBoxGlobals::fistMouse = true; // reset first mouse movement flag
			glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
				if (SandBoxGlobals::fistMouse) {
					lastX = xpos;
					lastY = ypos;
					SandBoxGlobals::fistMouse = false;
				}
				float xoffset = xpos - lastX;
				float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

				lastX = xpos;
				lastY = ypos;

				SandBoxGlobals::camera.ProcessMouseMovement(xoffset, yoffset);
				});
			glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
				SandBoxGlobals::camera.ProcessMouseScroll(yoffset);
				});
		}
		else {
			SandBoxGlobals::isOnMenu = true;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetCursorPosCallback(window, nullptr);
			glfwSetScrollCallback(window, nullptr);
		}
	}

	// ! Close window and program
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void SandBox::onImGui(ImGuiIO& io, Timestep timeStep) {
	ImGui::Begin("Ronin project");
	{
		ImGui::Text("Starter menu for Ronin project.");
		ImGui::Text("Thesis project to obtain a computer engeneer degree.");
		/* if (ImGui::ColorEdit4("clear color", voxel.getVoxelColor())) {
			updateBufferColor();
		} */
		ImGui::ColorEdit4("Light Color", glm::value_ptr(SandBoxGlobals::lightColor));

		ImGui::Checkbox("Wireframe View", &isViewInWireframe);
		ImGui::Text("Application \n average %.3f ms/frame \n(%.1f FPS)", timeStep.getMilliseconds(), io.Framerate);
	}
	ImGui::End();
}

/* void SandBox::updateBufferColor() {
	std::vector<float>* data = voxel.getVertexData();

	glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(float), data->data(), GL_DYNAMIC_DRAW);
} */

void SandBox::framebuffer_size_callback() {
	SandBoxGlobals::idViewPortChanged = false;
	projectionMatrix = glm::perspective(glm::radians(SandBoxGlobals::camera.Zoom), (float)SandBoxGlobals::width / (float)SandBoxGlobals::height, 0.1f, 100.0f);
}
