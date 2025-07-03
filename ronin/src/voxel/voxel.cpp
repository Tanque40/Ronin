#include "voxel/voxel.h"

Voxel::Voxel() {
	backTopLeftC = { -0.2f,  0.8f, 0.5f };
	backTopRightC = { 0.8f,  0.8f, 0.5f };
	backBottomLeftC = { -0.2f, -0.2f, 0.5f };
	backBottomRightC = { 0.8f, -0.2f, 0.5f };

	frontTopLeftC = { -0.5f,  0.5f, -0.5f };
	frontTopRightC = { 0.5f,  0.5f, -0.5f };
	frontBottomLeftC = { -0.5f, -0.5f, -0.5f };
	frontBottomRightC = { 0.5f, -0.5f, -0.5f };

	voxelOrigin = backTopRightC;
}

Voxel::Voxel(glm::vec3 voxelOrigin) {

}

Voxel::~Voxel() {

}

float* Voxel::getVoxelColor() {
	return (float*)&color;
}

void Voxel::setVoxelColor(glm::vec4 newColor) {
	color = newColor;
}

std::vector<float>* Voxel::getVertexData() {
	bool setColor = false;

	// ? Back face
	vertex.push_back(backTopRightC.x);
	vertex.push_back(backTopRightC.y);
	vertex.push_back(backTopRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(backBottomRightC.x);
	vertex.push_back(backBottomRightC.y);
	vertex.push_back(backBottomRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(backBottomLeftC.x);
	vertex.push_back(backBottomLeftC.y);
	vertex.push_back(backBottomLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(backTopLeftC.x);
	vertex.push_back(backTopLeftC.y);
	vertex.push_back(backTopLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);

	// ? Left face
	vertex.push_back(frontTopLeftC.x);
	vertex.push_back(frontTopLeftC.y);
	vertex.push_back(frontTopLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(frontBottomLeftC.x);
	vertex.push_back(frontBottomLeftC.y);
	vertex.push_back(frontBottomLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(backBottomLeftC.x);
	vertex.push_back(backBottomLeftC.y);
	vertex.push_back(backBottomLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(backTopLeftC.x);
	vertex.push_back(backTopLeftC.y);
	vertex.push_back(backTopLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);


	// ? Top face
	vertex.push_back(backTopRightC.x);
	vertex.push_back(backTopRightC.y);
	vertex.push_back(backTopRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(frontTopRightC.x);
	vertex.push_back(frontTopRightC.y);
	vertex.push_back(frontTopRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(frontTopLeftC.x);
	vertex.push_back(frontTopLeftC.y);
	vertex.push_back(frontTopLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(backTopLeftC.x);
	vertex.push_back(backTopLeftC.y);
	vertex.push_back(backTopLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);

	// ? Right face
	vertex.push_back(backTopRightC.x);
	vertex.push_back(backTopRightC.y);
	vertex.push_back(backTopRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(backBottomRightC.x);
	vertex.push_back(backBottomRightC.y);
	vertex.push_back(backBottomRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(frontBottomRightC.x);
	vertex.push_back(frontBottomRightC.y);
	vertex.push_back(frontBottomRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(frontTopRightC.x);
	vertex.push_back(frontTopRightC.y);
	vertex.push_back(frontTopRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);

	// ? Bottom face
	vertex.push_back(backBottomRightC.x);
	vertex.push_back(backBottomRightC.y);
	vertex.push_back(backBottomRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(frontBottomRightC.x);
	vertex.push_back(frontBottomRightC.y);
	vertex.push_back(frontBottomRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(frontBottomLeftC.x);
	vertex.push_back(frontBottomLeftC.y);
	vertex.push_back(frontBottomLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(backBottomLeftC.x);
	vertex.push_back(backBottomLeftC.y);
	vertex.push_back(backBottomLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);

	// ? Front face
	vertex.push_back(frontTopRightC.x);
	vertex.push_back(frontTopRightC.y);
	vertex.push_back(frontTopRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(frontBottomRightC.x);
	vertex.push_back(frontBottomRightC.y);
	vertex.push_back(frontBottomRightC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(frontBottomLeftC.x);
	vertex.push_back(frontBottomLeftC.y);
	vertex.push_back(frontBottomLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);
	vertex.push_back(frontTopLeftC.x);
	vertex.push_back(frontTopLeftC.y);
	vertex.push_back(frontTopLeftC.z);
	vertex.push_back(color.r);
	vertex.push_back(color.g);
	vertex.push_back(color.b);

	return &vertex;
}

std::string Voxel::toString() {
	std::string voxelData = "";

	voxelData += "Voxel: \n";
	voxelData += "\tBack Face: \n";
	voxelData += "\t\tx:" + std::to_string(backTopRightC.x);
	voxelData += " y:" + std::to_string(backTopRightC.y);
	voxelData += " z:" + std::to_string(backTopRightC.z);
	voxelData += "\n\t\tr:" + std::to_string(color.r);
	voxelData += " g:" + std::to_string(color.g);
	voxelData += " b:" + std::to_string(color.b);

	return voxelData;
}

