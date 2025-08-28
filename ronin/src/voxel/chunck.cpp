#include "roninpch.h"

#include "math.h"

#include "voxel/chunck.h"

Chunk::Chunk(unsigned int _sideCount) : sideCount(_sideCount) {
}

Chunk::~Chunk() {
}

void Chunk::generateChunk() {
	voxels.clear();
	data.clear();

	int sideCount = (int)this->sideCount;
	for (int x = -sideCount / 2; x < sideCount / 2; x++) {
		std::vector<std::vector<Voxel>> voxelRow;
		for (int y = -sideCount / 2; y < sideCount / 2; y++) {
			std::vector<Voxel> voxelColumn;
			for (int z = -sideCount / 2; z < sideCount / 2; z++) {
				if (sqrt(pow(z, 2) + pow(x, 2) + pow(y, 2)) < (sideCount / 2)) {
					glm::vec3 voxelOrigin(x, y, z);
					glm::vec4 voxelColor(
						static_cast<float>(rand() % 255) / 255.0f,
						static_cast<float>(rand() % 255) / 255.0f,
						static_cast<float>(rand() % 255) / 255.0f,
						1.0f // Alpha channel
					);
					voxelColumn.push_back(Voxel(voxelOrigin, voxelColor, 63));
					voxelCount++;
					quadCount += voxelColumn.back().getQuadCount(); // Update the quad count for the voxel
					triangleCount += voxelColumn.back().getQuadCount() * 2; // Each quad has 2 triangles
				}
			}
			voxelRow.push_back(voxelColumn);
		}
		voxels.push_back(voxelRow);
	}

}

std::vector<float>* Chunk::getData() {
	data.clear();
	for (auto& voxelRow : voxels) {
		for (auto& voxelColumn : voxelRow) {
			for (auto& voxel : voxelColumn) {
				std::vector<float>* voxelData = voxel.getVertexData();
				data.insert(data.end(), voxelData->begin(), voxelData->end());
			}
		}
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
		for (auto& voxelRow : voxels) {
			for (auto& voxelColumn : voxelRow) {
				for (auto& voxel : voxelColumn) {
					chunkData += voxel.toString() + "\n";
				}
			}
		}
	}

	return chunkData;
}
