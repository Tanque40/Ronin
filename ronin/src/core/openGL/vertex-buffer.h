#pragma once

class VertexBuffer {
private:
	unsigned int id; // OpenGL Vertex Buffer Object ID
	unsigned int dataSize;

public:
	VertexBuffer();
	~VertexBuffer();
	void bind(); // Bind the vertex buffer
	void unBind(); // Unbind the vertex buffer
	void setData(void* data, unsigned int size); // Set data for the vertex buffer
	unsigned int getDataSize() const { return dataSize / 4; }
	unsigned int getDataMemorySize() const { return dataSize; }
	unsigned int getId() const { return id; } // Get the ID of the vertex buffer
};
