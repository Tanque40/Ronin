#pragma once

#include "roninpch.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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

		const char* glsl_version = "#version 150";
#ifdef __APPLE__
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

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			return -1;
		}

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);

		float time = glfwGetTime(), lastFrameTime = glfwGetTime();
		Timestep timestep = time - lastFrameTime;
		lastFrameTime = time;
		// render loop
		// -----------
		spdlog::info("Ronin running");
		SandBox sandBox(window);
		sandBox.onAttach();

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
				ImGui::ShowDemoWindow();
				sandBox.onImGui(io, float(timestep));
			}
			// Rendering
			ImGui::Render();


			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		sandBox.onDetach();
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		glfwTerminate();
		return 0;
	}
};
