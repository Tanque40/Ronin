#pragma once
#include "roninpch.h"

#include <glm/glm.hpp>
#include <vector>

#include "voxel/voxel.h"

class Chunk {
private:
	std::vector<Voxel> voxels;
	std::vector<float> data;
	int voxelCount = 0; // Number of voxels in the chunk
	unsigned quadCount = 0; // Number of quads in the chunk
	int triangleCount = 0; // Number of triangles in the chunk

public:
	Chunk();
	~Chunk();

	void generateChunk();
	std::vector<float>* getData();
	std::string toString(bool showEachVoxelData);
};
