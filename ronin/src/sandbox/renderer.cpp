#include "sandbox/renderer.h"

Renderer::Renderer(Shader* _mainShader, std::vector<float>* _data) : mainShader(_mainShader), data(_data) {

}

Renderer::~Renderer() {
	// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Renderer::start() {
	for (size_t i = 0; i < data->size() / 4; i += 6) {
		indices.push_back(0 + (4 * i / 6));
		indices.push_back(1 + (4 * i / 6));
		indices.push_back(3 + (4 * i / 6));
		indices.push_back(2 + (4 * i / 6));
		indices.push_back(1 + (4 * i / 6));
		indices.push_back(3 + (4 * i / 6));
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data->size() * sizeof(float), data->data(), GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW);

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
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0); // no need to unbind it every times
}
