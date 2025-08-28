#include "roninpch.h"

#include "sandbox/renderer.h"

Renderer::Renderer(VertexBuffer* _vb, Shader* _mainShader) : mainShader(_mainShader), vb(_vb) {

}

Renderer::~Renderer() {
	// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
}

void Renderer::start() {
	spdlog::info("Renderer started");
	int indicesCount = (vb->getDataSize() / 10) + (2 * (vb->getDataSize() / 10 / 4)) + 1;
	for (size_t i = 0; i < indicesCount; i += 6) {
		indices.push_back(0 + (4 * i / 6));
		indices.push_back(1 + (4 * i / 6));
		indices.push_back(3 + (4 * i / 6));
		indices.push_back(2 + (4 * i / 6));
		indices.push_back(1 + (4 * i / 6));
		indices.push_back(3 + (4 * i / 6));
	}

	/*
	spdlog::info("Renderer started with {} vertices and {} indices", vb->getDataSize() / 7, indices.size());
	spdlog::info("indices: ");
	for (size_t i = 0; i < indices.size(); i += 6) {
		spdlog::info(
			"Quad {}:\n\t{} {} {}\n\t{} {} {}",
			i / 6,
			indices[i], indices[i + 1], indices[i + 2],
			indices[i + 3], indices[i + 4], indices[i + 5]);
	}
	*/

	glGenVertexArrays(1, &VAO);

	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	vb->bind();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STREAM_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(7 * sizeof(float)));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::draw(glm::mat4 projectionMatrix, glm::mat4 modelMatrix) {
	// render
		// ------
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// draw our first triangle
	mainShader->bind();
	mainShader->SetUniformsMat4f("projection", projectionMatrix);
	mainShader->SetUniformsMat4f("view", SandBoxGlobals::camera.GetViewMatrix());
	mainShader->SetUniformsMat4f("model", modelMatrix);
	mainShader->SetUniformsVec3f("cameraPos", SandBoxGlobals::camera.GetPosition());
	mainShader->SetUniformsVec4f("lightColor", SandBoxGlobals::lightColor);
	//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	vb->bind();
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0); // no need to unbind it every times
}
