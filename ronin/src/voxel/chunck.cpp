#include "roninpch.h"

#include "math.h"

#include "voxel/chunck.h"
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
Chunk::Chunk(unsigned int _sideCount) : sideCount(_sideCount) {
}

Chunk::~Chunk() {
}

void Chunk::generateChunk() {
	voxels.clear();
	data.clear();

	int sideCount = (int)this->sideCount;
	// Parámetros de ruido (AJUSTA ESTOS VALORES para cambiar el terreno)
	float frequency = 0.05f; // "Zoom". Menor valor = montañas más anchas/suaves.
	float amplitude = 10.0f; // "Altura". Mayor valor = montañas más altas.
	float baseHeight = 0.0f; // Altura base del suelo (nivel del mar)

	for (int x = -sideCount / 2; x < sideCount / 2; x++) {
		std::vector<std::vector<Voxel>> voxelRow;
		for (int z = -sideCount / 2; z < sideCount / 2; z++) {
			std::vector<Voxel> voxelColumn;

			// 1. Calcular la altura del terreno en esta posición X, Z
			// Usamos vec2 porque la altura depende del plano horizontal
			glm::vec2 noisePos = glm::vec2(x, z) * frequency;

			// glm::perlin devuelve valores entre -1 y 1.
			float noiseValue = glm::perlin(noisePos);

			// Convertimos el ruido en una altura en el mundo (ej: altura 5, altura -3)
			int terrainHeight = static_cast<int>(baseHeight + (noiseValue * amplitude));

			for (int y = -sideCount / 2; y < sideCount / 2; y++) {
				// 2. Decidir si ponemos un bloque
				// Si la Y actual es menor o igual a la altura del terreno, ponemos bloque.
				if (y <= terrainHeight) {


					// La posición es EXACTA en la grilla (sin sumar ruido a la posición)
					glm::vec3 voxelOrigin(x, y, z);

					// Color básico basado en altura (opcional, para debug visual)
					glm::vec4 voxelColor;
					if (y == terrainHeight) // Capa superior (pasto)
						voxelColor = glm::vec4(0.2f, 0.8f, 0.2f, 1.0f);
					else // Tierra/Piedra
						voxelColor = glm::vec4(0.5f, 0.3f, 0.1f, 1.0f);

					voxelColumn.push_back(Voxel(voxelOrigin, voxelColor, 63));
					voxelCount++;
				}
				// Si y > terrainHeight, es aire, no hacemos push_back (o agregamos bloque de aire)
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
				// Update the voxel's quad and triangle counts
				quadCount += voxel.getQuadCount();
				triangleCount += voxel.getQuadCount() * 2;
				data.insert(data.end(), voxelData->begin(), voxelData->end());
			}
		}
	}

	return &data;
}

std::string Chunk::toString(bool showEachVoxelData) {
	std::string chunkData = "\tChunk: \n";
	chunkData += "\t\tVoxels count: " + std::to_string(voxelCount) + "\n";
	chunkData += "\t\tQuads count: " + std::to_string(quadCount) + "\n";
	chunkData += "\t\tTriangles count: " + std::to_string(triangleCount);

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
