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

	// ? In theory we can use only one point to define the voxel, but just commenting out the rest of the points for now.
	/* glm::vec3 frontTopLeftC, frontTopRightC, frontBottomLeftC, frontBottomRightC;
	glm::vec3 backTopLeftC, backTopRightC, backBottomLeftC, backBottomRightC; */
	glm::vec3 voxelOrigin; // * By this moment backBottomLeftC is the origin of the voxel
	glm::vec4 color; // * Default white
	std::vector<float> vertex;
	bool isActive = true; // * If the voxel is active or not

	/*
	 * I will use a bits as a reference to the show / dont show sides of the voxel.
	 *  0 => 000000 -> All sides are hide
	 *  1 => 000001 -> Show back
	 *  2 => 000010 -> Show leftSide
	 *  4 => 000100 -> Show bottom
	 *  8 => 001000 -> Show rightSide
	 * 16 => 010000 -> Show top
	 * 32 => 100000 -> Show front 010010
	 * and any combination of these bits will show the respective sides.
	 * For example:
	 * 63 => 111111 -> Show all sides
	 */
	u_int8_t voxelSides; // * Each voxel has 6 sides (quads)
	u_int8_t quadCount = 0; // * Each voxel has 6 quads

public:
	Voxel();
	Voxel(glm::vec3 voxelOrigin);
	Voxel(glm::vec3 _voxelOrigin = { 0.0f, 0.0f, 0.0f }, glm::vec4 _color = { 1.0f, 1.0f, 1.0f, 1.0f });
	Voxel(glm::vec3 _voxelOrigin = { 0.0f, 0.0f, 0.0f }, glm::vec4 _color = { 1.0f, 1.0f, 1.0f, 1.0f }, uint8_t _voxelSides = 63);

	~Voxel();

	bool isVoxelActive() const { return isActive; }
	void setVoxelActive(bool active) { isActive = active; }

	uint8_t getQuadCount() const { return quadCount; }
	float* getVoxelColor();
	void setVoxelColor(glm::vec4 newColor);

	std::vector<float>* getVertexData();

	std::string toString();
};
