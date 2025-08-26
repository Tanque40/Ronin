#pragma once

class VertexBuffer {
private:
	unsigned int id; // OpenGL Vertex Buffer Object ID

public:
	VertexBuffer();
	~VertexBuffer();
	void bind(); // Bind the vertex buffer
	void unBind(); // Unbind the vertex buffer
	void setData(void* data, unsigned int size); // Set data for the vertex buffer
	unsigned int getId() const { return id; } // Get the ID of the vertex buffer
};
