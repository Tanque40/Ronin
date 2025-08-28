#include "roninpch.h"

#include  "core/openGL/vertex-buffer.h"

VertexBuffer::VertexBuffer() : id(0), dataSize(0) { // Initialize 'id' to 0
	glGenBuffers(1, &id);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &id);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unBind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::setData(void* data, unsigned int size) {
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STREAM_DRAW);
	dataSize = size;
}
