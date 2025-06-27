#include "sandbox/renderer.h"

Renderer::Renderer(Shader* _mainShader, float* _data) : mainShader(_mainShader), data(_data) {

}

Renderer::~Renderer() {
	// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Renderer::start() {
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

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 24 * 6 * sizeof(float), data, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
}

void Renderer::draw(glm::mat4 projectionMatrix, glm::mat4 modelMatrix) {
	// render
		// ------
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// draw our first triangle
	mainShader->bind();
	mainShader->SetUniformsMat4f("projection", projectionMatrix);
	mainShader->SetUniformsMat4f("view", SandBoxGlobals::camera.GetViewMatrix());
	mainShader->SetUniformsMat4f("model", modelMatrix);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0); // no need to unbind it every times
}
