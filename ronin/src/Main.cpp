#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader/shader.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1080;
const unsigned int SCR_HEIGHT = 720;

unsigned int SCR_WIDTH_EX = 1080;
unsigned int SCR_HEIGHT_EX = 720;

int main(void) {
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

	glm::vec3 x(0.0f, 1.0f, 2.5f);
	std::cout << x.z << std::endl;

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
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	//glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH_EX / (float)SCR_HEIGHT_EX, 0.1f, 100.0f);
	glm::mat4 projectionMatrix = glm::ortho(
		(float)SCR_WIDTH_EX / -2.0f,
		(float)SCR_WIDTH_EX / 2.0f,
		(float)SCR_HEIGHT_EX / -2.0f,
		(float)SCR_HEIGHT_EX / 2.0f,
		-1000.0f,
		1000.0f);
	std::cout << projectionMatrix[0][0] << std::endl;
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

		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
			ImGui::Checkbox("Another Window", &show_another_window);

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
			ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application \n average %.3f ms/frame \n(%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
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
		mainShader.SetuniformsMat4f("projection", projectionMatrix);
		mainShader.SetuniformsMat4f("view", viewMatrix);
		mainShader.SetuniformsMat4f("model", modelMatrix);
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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);

	SCR_WIDTH_EX = width;
	SCR_HEIGHT_EX = height;
}
