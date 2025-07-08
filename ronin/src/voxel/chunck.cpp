#include "roninpch.h"

#include "voxel/chunck.h"

Chunk::Chunk() {
}

Chunk::~Chunk() {
}

int sideCount = 10; // Number of voxels per side in the chunk

void Chunk::generateChunk() {
	voxels.clear();
	data.clear();

	// Generate a 10x10x10 chunk of voxels
	for (int x = 0; x < sideCount; x += 1) {
		for (int y = 0; y < sideCount; y += 1) {
			for (int z = 0; z < sideCount; z += 1) {
				glm::vec3 voxelOrigin(x, y, z);
				glm::vec4 voxelColor(
					static_cast<float>(rand() % 255) / 255.0f,
					static_cast<float>(rand() % 255) / 255.0f,
					static_cast<float>(rand() % 255) / 255.0f,
					1.0f // Alpha channel
				);
				voxels.emplace_back(voxelOrigin, voxelColor, 1);
				voxelCount++;
				quadCount += 6; // Each voxel contributes 6 quads
				triangleCount += 12; // Each voxel contributes 12 triangles
			}
		}
	}
}

std::vector<float>* Chunk::getData() {
	data.clear();
	for (auto& voxel : voxels) {
		std::vector<float>* voxelData = voxel.getVertexData();
		data.insert(data.end(), voxelData->begin(), voxelData->end());
	}

	return &data;
}

std::string Chunk::toString(bool showEachVoxelData) {
	std::string chunkData = "Chunk: \n";
	chunkData += "\tVoxels count: " + std::to_string(voxelCount) + "\n";
	chunkData += "\tQuads count: " + std::to_string(quadCount) + "\n";
	chunkData += "\tTriangles count: " + std::to_string(triangleCount) + "\n";

	if (showEachVoxelData) {
		chunkData += "Voxels data:\n";
		for (auto& voxel : voxels) {
			chunkData += voxel.toString() + "\n";
		}
	}

	return chunkData;
}
