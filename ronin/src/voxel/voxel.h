#pragma once
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
	glm::vec3 voxelOrigin; // ? By this moment backTopRightC
	glm::vec4 color = { 0.5f, 0.5f, 1.0f, 1.0f }; // ? Default white
	std::vector<float> vertex;

public:
	Voxel();
	Voxel(glm::vec3 voxelOrigin);
	~Voxel();

	float* getVoxelColor();
	void setVoxelColor(glm::vec4 newColor);

	std::vector<float>* getVertexData();

	std::string toString();
};
