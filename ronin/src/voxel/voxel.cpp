#include "roninpch.h"

#include "voxel/voxel.h"

Voxel::Voxel() {
	/* backTopLeftC = { -0.2f,  0.8f, 0.5f };
	backTopRightC = { 0.8f,  0.8f, 0.5f };
	backBottomLeftC = { -0.2f, -0.2f, 0.5f };
	backBottomRightC = { 0.8f, -0.2f, 0.5f };

	frontTopLeftC = { -0.5f,  0.5f, -0.5f };
	frontTopRightC = { 0.5f,  0.5f, -0.5f };
	frontBottomLeftC = { -0.5f, -0.5f, -0.5f };
	frontBottomRightC = { 0.5f, -0.5f, -0.5f }; */

	// * backBottomLeftC
	voxelOrigin = { 0.0f, 0.0f, 0.0f };
}

Voxel::Voxel(glm::vec3 _voxelOrigin) : voxelOrigin(_voxelOrigin) {
}

Voxel::Voxel(glm::vec3 _voxelOrigin, glm::vec4 _color) : voxelOrigin(_voxelOrigin), color(_color) {
	/* backTopLeftC = { voxelOrigin.x - 1.0f, voxelOrigin.y, voxelOrigin.z };
	backTopRightC = voxelOrigin;
	backBottomLeftC = { voxelOrigin.x - 1.0f, voxelOrigin.y - 1.0f, voxelOrigin.z };
	backBottomRightC = { voxelOrigin.x , voxelOrigin.y - 1.0f, voxelOrigin.z };

	frontTopLeftC = { voxelOrigin.x - 1.0f, voxelOrigin.y, voxelOrigin.z - 1.0f };
	frontTopRightC = { voxelOrigin.x , voxelOrigin.y , voxelOrigin.z - 1.0f };
	frontBottomLeftC = { voxelOrigin.x - 1.0f, voxelOrigin.y - 1.0f, voxelOrigin.z - 1.0f };
	frontBottomRightC = { voxelOrigin.x , voxelOrigin.y - 1.0f, voxelOrigin.z - 1.0f }; */
}

Voxel::Voxel(glm::vec3 _voxelOrigin, glm::vec4 _color, u_int8_t _voxelSides)
	: voxelOrigin(_voxelOrigin), color(_color), voxelSides(_voxelSides) {
}

Voxel::~Voxel() {
	// * Destructor
	// * No dynamic memory allocation, so nothing to free
	// * Just in case, clear the vertex data
	vertex.clear();
	// * Clear the color
	color = { 1.0f, 1.0f, 1.0f, 1.0f };
	// * Clear the voxel origin
	voxelOrigin = { 0.0f, 0.0f, 0.0f };
	// * Clear the voxel sides
	voxelSides = 0; // * Clear the voxel sides
}

float* Voxel::getVoxelColor() {
	return (float*)&color;
}

void Voxel::setVoxelColor(glm::vec4 newColor) {
	color = newColor;
}

std::vector<float>* Voxel::getVertexData() {
	vertex.clear();

	// * Check back side
	if (voxelSides & 1) {
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		quadCount++;
	}

	// * Check left side
	voxelSides >>= 1;
	if (voxelSides & 1) {
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		quadCount++;
	}

	// * Check bottom side
	voxelSides >>= 1;
	if (voxelSides & 1) {
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		quadCount++;
	}

	// * Check right side
	voxelSides >>= 1;
	if (voxelSides & 1) {
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		quadCount++;
	}

	// * Check top side
	voxelSides >>= 1;
	if (voxelSides & 1) {
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		quadCount++;
	}

	// * Check front side
	voxelSides >>= 1;
	if (voxelSides & 1) {
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x + 1.0f);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		vertex.push_back(voxelOrigin.x);
		vertex.push_back(voxelOrigin.y + 1.0f);
		vertex.push_back(voxelOrigin.z + 1.0f);
		vertex.push_back(color.r);
		vertex.push_back(color.g);
		vertex.push_back(color.b);
		vertex.push_back(color.a);
		quadCount++;
	}


	return &vertex;
}

std::string Voxel::toString() {
	std::string voxelData = "";

	voxelData += "Voxel: \n";
	voxelData += "\tOrigin: \n";
	voxelData += "\t\tx:" + std::to_string(voxelOrigin.x);
	voxelData += " y:" + std::to_string(voxelOrigin.y);
	voxelData += " z:" + std::to_string(voxelOrigin.z);
	voxelData += "\n\tColor: \n";
	voxelData += "\t\tr:" + std::to_string(color.r);
	voxelData += " g:" + std::to_string(color.g);
	voxelData += " b:" + std::to_string(color.b);
	voxelData += " a:" + std::to_string(color.a);
	voxelData += "\n\tQuad Count: " + std::to_string(quadCount);

	return voxelData;
}

