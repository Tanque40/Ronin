#pragma once

#include "roninpch.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "sandbox/sandbox.h"
#include "core/timestep.h"

class Application {
public:
	// settings
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	static int Run() {
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

#ifdef __APPLE__
		const char* glsl_version = "#version 150";
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
		// glfw window creation
		// --------------------
		GLFWwindow* window = glfwCreateWindow(Application::SCR_WIDTH, Application::SCR_HEIGHT, "Ronin Project", NULL, NULL);
		if (window == NULL) {
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);


		// glew: load all OpenGL function pointers
		// ---------------------------------------
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			glfwTerminate();
			return -1;
		}

		SandBox sandBox(window);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		sandBox.onAttach();
		float time = glfwGetTime(), lastFrameTime = glfwGetTime();
		Timestep timestep = time - lastFrameTime;
		lastFrameTime = time;
		// render loop
		// -----------
		while (!glfwWindowShouldClose(window)) {
			time = glfwGetTime();
			timestep = time - lastFrameTime;
			lastFrameTime = time;

			sandBox.onUpdate(float(timestep));

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				sandBox.onImGui(io, float(timestep));
			}
			// Rendering
			ImGui::Render();


			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwPollEvents();
			glfwSwapBuffers(window);
		}

		sandBox.onDetach();


		return 0;
	}
};
