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
	// ? Back face
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

	// ? Left face  e
	vertex[24] = frontTopLeftC.x;
	vertex[25] = frontTopLeftC.y;
	vertex[26] = frontTopLeftC.z;
	vertex[27] = color.r;
	vertex[28] = color.g;
	vertex[29] = color.b;
	vertex[30] = frontBottomLeftC.x;
	vertex[31] = frontBottomLeftC.y;
	vertex[32] = frontBottomLeftC.z;
	vertex[33] = color.r;
	vertex[34] = color.g;
	vertex[35] = color.b;
	vertex[36] = backBottomLeftC.x;
	vertex[37] = backBottomLeftC.y;
	vertex[38] = backBottomLeftC.z;
	vertex[39] = color.r;
	vertex[40] = color.g;
	vertex[41] = color.b;
	vertex[42] = backTopLeftC.x;
	vertex[43] = backTopLeftC.y;
	vertex[44] = backTopLeftC.z;
	vertex[45] = color.r;
	vertex[46] = color.g;
	vertex[47] = color.b;

	// ? Top face
	vertex[48] = backTopRightC.x;
	vertex[49] = backTopRightC.y;
	vertex[50] = backTopRightC.z;
	vertex[51] = color.r;
	vertex[52] = color.g;
	vertex[53] = color.b;
	vertex[54] = frontTopRightC.x;
	vertex[55] = frontTopRightC.y;
	vertex[56] = frontTopRightC.z;
	vertex[57] = color.r;
	vertex[58] = color.g;
	vertex[59] = color.b;
	vertex[60] = frontTopLeftC.x;
	vertex[61] = frontTopLeftC.y;
	vertex[62] = frontTopLeftC.z;
	vertex[63] = color.r;
	vertex[64] = color.g;
	vertex[65] = color.b;
	vertex[66] = backTopLeftC.x;
	vertex[67] = backTopLeftC.y;
	vertex[68] = backTopLeftC.z;
	vertex[69] = color.r;
	vertex[70] = color.g;
	vertex[71] = color.b;

	// ? Right face
	vertex[72] = backTopRightC.x;
	vertex[73] = backTopRightC.y;
	vertex[74] = backTopRightC.z;
	vertex[75] = color.r;
	vertex[76] = color.g;
	vertex[77] = color.b;
	vertex[78] = backBottomRightC.x;
	vertex[79] = backBottomRightC.y;
	vertex[80] = backBottomRightC.z;
	vertex[81] = color.r;
	vertex[82] = color.g;
	vertex[83] = color.b;
	vertex[84] = frontBottomLeftC.x;
	vertex[85] = frontBottomLeftC.y;
	vertex[86] = frontBottomLeftC.z;
	vertex[87] = color.r;
	vertex[88] = color.g;
	vertex[89] = color.b;
	vertex[90] = frontTopLeftC.x;
	vertex[91] = frontTopLeftC.y;
	vertex[92] = frontTopLeftC.z;
	vertex[93] = color.r;
	vertex[94] = color.g;
	vertex[95] = color.b;

	// ? Bottom face
	vertex[96] = backBottomRightC.x;
	vertex[97] = backBottomRightC.y;
	vertex[98] = backBottomRightC.z;
	vertex[99] = color.r;
	vertex[100] = color.g;
	vertex[101] = color.b;
	vertex[102] = frontBottomRightC.x;
	vertex[103] = frontBottomRightC.y;
	vertex[104] = frontBottomRightC.z;
	vertex[105] = color.r;
	vertex[106] = color.g;
	vertex[107] = color.b;
	vertex[108] = frontBottomLeftC.x;
	vertex[109] = frontBottomLeftC.y;
	vertex[110] = frontBottomLeftC.z;
	vertex[111] = color.r;
	vertex[112] = color.g;
	vertex[113] = color.b;
	vertex[114] = backBottomLeftC.x;
	vertex[115] = backBottomLeftC.y;
	vertex[116] = backBottomLeftC.z;
	vertex[117] = color.r;
	vertex[118] = color.g;
	vertex[119] = color.b;

	// ? Front face
	vertex[120] = frontTopRightC.x;
	vertex[121] = frontTopRightC.y;
	vertex[122] = frontTopRightC.z;
	vertex[123] = color.r;
	vertex[124] = color.g;
	vertex[125] = color.b;
	vertex[126] = frontBottomRightC.x;
	vertex[127] = frontBottomRightC.y;
	vertex[128] = frontBottomRightC.z;
	vertex[129] = color.r;
	vertex[130] = color.g;
	vertex[131] = color.b;
	vertex[132] = frontBottomLeftC.x;
	vertex[133] = frontBottomLeftC.y;
	vertex[134] = frontBottomLeftC.z;
	vertex[135] = color.r;
	vertex[136] = color.g;
	vertex[137] = color.b;
	vertex[138] = frontTopLeftC.x;
	vertex[139] = frontTopLeftC.y;
	vertex[140] = frontTopLeftC.z;
	vertex[141] = color.r;
	vertex[142] = color.g;
	vertex[143] = color.b;

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

