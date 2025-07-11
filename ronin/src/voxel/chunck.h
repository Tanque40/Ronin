#pragma once
#include "roninpch.h"

#include <glm/glm.hpp>
#include <vector>

#include "voxel/voxel.h"

class Chunk {
private:
	unsigned int sideCount; // Number of voxels per side in the chunk
	std::vector<std::vector<std::vector<Voxel>>> voxels;
	std::vector<float> data;

	int voxelCount = 0; // Number of voxels in the chunk
	unsigned quadCount = 0; // Number of quads in the chunk
	int triangleCount = 0; // Number of triangles in the chunk

public:
	Chunk(unsigned int sideCount = 10);
	~Chunk();

	void generateChunk();

	std::vector<float>* getData();
	std::string toString(bool showEachVoxelData = false);

private:
	// TODO decide the logic to determine if a face should be shown
	void checkFacesToShow();

	bool shouldShowFace(Voxel* origin, Voxel* neighbor, u_int8_t faceBit);
};
