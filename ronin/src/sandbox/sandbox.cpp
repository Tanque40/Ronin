#include "sandbox/sandbox.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

SandBox::SandBox() {

}

SandBox::~SandBox() {
}

void SandBox::onAttach() {
	camera = Camera(glm::vec3(0.0f, 0.0f, 10.0f));
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
		21, 22, 23
	};


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);


	float* data = voxel.getVertexData();

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 24 * 6 * sizeof(float), data, GL_DYNAMIC_DRAW);
	//std::cout << "x: " << voxel.getVertexData()[0]<< "y: " << voxel.getVertexData()[1]<< "z: " << voxel.getVertexData()[2]<< "r: " << voxel.getVertexData()[3]<< "g: " << voxel.getVertexData()[4]<< "b: " << voxel.getVertexData()[5]<< "a: " << voxel.getVertexData()[6]<<std::endl;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// build and compile our shader program
	// ------------------------------------
	mainShader = new Shader("res/shaders/initial.vs.glsl", "res/shaders/initial.fs.glsl");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	// note that we're translating the scene in the reverse direction of where we want to move
	viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -10.0f));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
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
	// render
	// ------
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// draw our first triangle
	mainShader->bind();
	mainShader->SetUniformsMat4f("projection", projectionMatrix);
	mainShader->SetUniformsMat4f("view", camera.GetViewMatrix());
	mainShader->SetUniformsMat4f("model", modelMatrix);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0); // no need to unbind it every time
}

void SandBox::onEvent() {
}

void SandBox::onImGui( ImGuiIO& io ) {
	ImGui::Begin("Ronin project");
	ImGui::Text("Started menu for Ronin project.");
	ImGui::Text("Thesis project to obtain a computer engeneer degree.");
	if(ImGui::ColorEdit4("clear color", voxel.getVoxelColor()))
		updateBufferColor();
	ImGui::Text(voxel.toString().c_str());
	ImGui::Text("Application \n average %.3f ms/frame \n(%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();
}

void SandBox::updateBufferColor(){
	float* data = voxel.getVertexData();

	glBufferData(GL_ARRAY_BUFFER, 24 * 6 * sizeof(float), data, GL_DYNAMIC_DRAW);
}
