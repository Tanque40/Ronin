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

float* Voxel::getVoxelColor(){
	return (float*) &color;
}

void Voxel::setVoxelColor(glm::vec4 newColor){
	color = newColor;
}

float* Voxel::getVertexData(){

	vertex[0] = backTopRightC.x;
	vertex[1] = backTopRightC.y;
	vertex[2] = backTopRightC.z;
	vertex[3] = color.r;
	vertex[4] = color.g;
	vertex[5] = color.b;
	vertex[6] = backBottomRightC.x;
	vertex[7] = backBottomRightC.y;
	vertex[8] = backBottomRightC.z;
	vertex[9] = color.r;
	vertex[10] = color.g;
	vertex[11] = color.b;
	vertex[12] = backBottomLeftC.x;
	vertex[13] = backBottomLeftC.y;
	vertex[14] = backBottomLeftC.z;
	vertex[15] = color.r;
	vertex[16] = color.g;
	vertex[17] = color.b;
	vertex[18] = backTopLeftC.x;
	vertex[19] = backTopLeftC.y;
	vertex[20] = backTopLeftC.z;
	vertex[21] = color.r;
	vertex[22] = color.g;
	vertex[23] = color.b;

	vertex[24] = frontTopRightC.x;
	vertex[25] = frontTopRightC.y;
	vertex[26] = frontTopRightC.z;
	vertex[27] = color.r;
	vertex[28] = color.g;
	vertex[29] = color.b;
	vertex[30] = frontBottomRightC.x;
	vertex[31] = frontBottomRightC.y;
	vertex[32] = frontBottomRightC.z;
	vertex[33] = color.r;
	vertex[34] = color.g;
	vertex[35] = color.b;
	vertex[36] = frontBottomLeftC.x;
	vertex[37] = frontBottomLeftC.y;
	vertex[38] = frontBottomLeftC.z;
	vertex[39] = color.r;
	vertex[40] = color.g;
	vertex[41] = color.b;
	vertex[42] = frontTopLeftC.x;
	vertex[43] = frontTopLeftC.y;
	vertex[44] = frontTopLeftC.z;
	vertex[45] = color.r;
	vertex[46] = color.g;
	vertex[47] = color.b;

	return vertex;
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

