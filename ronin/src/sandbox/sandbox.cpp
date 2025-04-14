#include "sandbox/sandbox.h"

#include <charconv>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>
#include <string>

SandBox::SandBox() {

}

SandBox::~SandBox() {
}

void SandBox::onAttach() {
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

	// build and compile our shader program
	// ------------------------------------
	mainShader = new Shader("res/shaders/initial.vs.glsl", "res/shaders/initial.fs.glsl");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	// note that we're translating the scene in the reverse direction of where we want to move
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(100.0f));
	spdlog::info("Ronin running");

}

void SandBox::onDetach() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void SandBox::onUpdate() {
	// draw our first triangle
	mainShader->bind();
	mainShader->SetUniformsMat4f("projection", projectionMatrix);
	mainShader->SetUniformsMat4f("view", viewMatrix);
	mainShader->SetUniformsMat4f("model", modelMatrix);
	mainShader->SetUniform4f("cubeColor", cubeColor);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 50, GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0); // no need to unbind it every time
}

void SandBox::onEvent() {
}

void SandBox::onImGui( ImGuiIO& io ) {
	ImGui::Begin("Ronin project");
	ImGui::Text("Started menu for Ronin project.");
	ImGui::Text("Thesis project to obtain a computer engeneer degree.");
	ImGui::ColorEdit4("clear color", (float*)&cubeColor);
	std::string textTest = std::to_string(modelMatrix[0][0]);
	ImGui::Text(textTest.c_str());
	ImGui::Text("Application \n average %.3f ms/frame \n(%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();
}
