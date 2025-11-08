#pragma once
#include "roninpch.h"

#include "sandbox/camera.h"

class SandBoxGlobals {
public:
	static Camera camera;
	static unsigned int width, height;
	static bool isViewPortChanged;
	static bool isOnMenu;
	static bool firstMouse;
	static glm::vec4 lightColor;
};
