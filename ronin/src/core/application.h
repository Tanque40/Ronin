#pragma once

#include "roninpch.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader/shader.h"

class Application {
private:
	// settings
	static const unsigned int SCR_WIDTH = 1080;
	static const unsigned int SCR_HEIGHT = 720;

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void processInput(GLFWwindow* window);
public:
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
		GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Ronin Project", NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// glew: load all OpenGL function pointers
		// ---------------------------------------
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			glfwTerminate();
			return -1;
		}

		// build and compile our shader program
		// ------------------------------------
		Shader mainShader("res/shaders/initial.vs.glsl", "res/shaders/initial.fs.glsl");

		// set up vertex data (and buffer(s)) and configure vertex attributes
		// ------------------------------------------------------------------
		float vertices[] = {
			// * front face
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f,   // top left

			// * back face
			 0.8f,  0.8f, 0.5f,  // top right
			 0.8f, -0.2f, 0.5f,  // bottom right
			-0.2f, -0.2f, 0.5f,  // bottom left
			-0.2f,  0.8f, 0.5f,   // top left

			// * left face
			-0.5f,  0.5f, 0.0f,  // top right
			-0.5f, -0.5f, 0.0f,  // bottom right
			-0.2f, -0.2f, 0.5f,  // bottom left
			-0.2f,  0.8f, 0.0f,   // top left

			// * right face
			 0.8f,  0.8f, 0.5f,  // top right
			 0.8f, -0.2f, 0.5f,  // bottom right
			 0.5f, -0.5f, 0.0f,  // bottom left
			 0.5f,  0.5f, 0.0f,   // top left

			 // * bottom face
			 0.8f, -0.2f, 0.5f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.2f, -0.2f, 0.5f,   // top left

			// * top face
			 0.8f,  0.8f, 0.5f,  // top right
			 0.5f,  0.5f, 0.0f,  // bottom right
			-0.5f,  0.5f, 0.0f,  // bottom left
			-0.2f,  0.8f, 0.5f,   // top left
		};
		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 3,
			1, 2, 3,

			4, 5, 7,
			5, 6, 7,

			8, 9, 11,
			9, 10, 11,

			12, 13, 15,
			13, 14, 15,

			16, 17, 19,
			17, 18, 19,

			20, 21, 23,
			21, 22, 23,
		};
		unsigned int VBO, VAO, EBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);


		// uncomment this call to draw in wireframe polygons.
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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

		bool show_another_window = false;
		glm::vec4 cubeColor(0.45f, 0.55f, 0.60f, 1.00f);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_ALWAYS);

		//glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH_EX / (float)SCR_HEIGHT_EX, 0.1f, 100.0f);
		glm::mat4 projectionMatrix = glm::ortho(
			(float)SCR_WIDTH / -2.0f,
			(float)SCR_WIDTH / 2.0f,
			(float)SCR_HEIGHT / -2.0f,
			(float)SCR_HEIGHT / 2.0f,
			-1000.0f,
			1000.0f
		);

		glm::mat4 viewMatrix = glm::mat4(1.0f);
		// note that we're translating the scene in the reverse direction of where we want to move
		viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

		glm::mat4 modelMatrix = glm::mat4(1.0f);
		modelMatrix = glm::scale(modelMatrix, glm::vec3(100.0f));

		// render loop
		// -----------
		while (!glfwWindowShouldClose(window)) {
			// input
			// -----
			processInput(window);

			// Start the Dear ImGui frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			{
				ImGui::Begin("Ronin project");
				ImGui::Text("Started menu for Ronin project.");
				ImGui::Text("Thesis project to obtain a computer engeneer degree.");
				ImGui::ColorEdit4("clear color", (float*)&cubeColor);
				ImGui::Text("Application \n average %.3f ms/frame \n(%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
			}

			// Rendering
			ImGui::Render();

			// render
			// ------
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// draw our first triangle
			mainShader.bind();
			mainShader.SetUniformsMat4f("projection", projectionMatrix);
			mainShader.SetUniformsMat4f("view", viewMatrix);
			mainShader.SetUniformsMat4f("model", modelMatrix);
			mainShader.SetUniform4f("cubeColor", cubeColor);
			glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
			// glBindVertexArray(0); // no need to unbind it every time
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
			// -------------------------------------------------------------------------------
			glfwSwapBuffers(window);
			glfwPollEvents();

		}

		// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
		return 0;
	}
};
