#include "roninpch.h"

#include  "core/openGL/vertex-buffer.h"

VertexBuffer::VertexBuffer() : id(0) { // Initialize 'id' to 0
	glGenBuffers(1, &id);
}

VertexBuffer::~VertexBuffer(){
}

void VertexBuffer::bind(){
}

void VertexBuffer::unBind(){
}

void VertexBuffer::setData( void* data, unsigned int size ){
}
