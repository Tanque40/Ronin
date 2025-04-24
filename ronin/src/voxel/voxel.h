#include "roninpch.h"

#include <glm/glm.hpp>

class Voxel {
private:
	// * ====================================
	//
	// *        backTopLeftC -> -------- <- backTopRightC
	// *            	      /|      /|
	// *	                 / |	 / |
	// *  frontTopLeftC  ->  |-------|<|--- frontTopRightC
	// *  backBottomLeftC -> | |-----|-/ <- backBottomRightC
	// *                     |/      |/
	// * frontBottomLeftC -> |-------| <- frontBottomRightC
	//
	// * ====================================
	glm::vec3 frontTopLeftC, frontTopRightC, frontBottomLeftC, frontBottomRightC;
	glm::vec3 backTopLeftC, backTopRightC, backBottomLeftC, backBottomRightC;
	glm::vec3 voxelOrigin; // ? By this moment backTopRightCC
	glm::vec4 color = { 0.5f, 0.5f, 1.0f, 1.0f }; // ? Default whiteo
	float vertex[48];

public:
	Voxel();
	Voxel(glm::vec3 voxelOrigin);
	~Voxel();

	float* getVoxelColor();
	void setVoxelColor(glm::vec4 newColor);

	float* getVertexData();

	std::string toString();
};
