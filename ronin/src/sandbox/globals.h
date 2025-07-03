#pragma once
#include <GL/glew.h>

#include "sandbox/camera.h"

class SandBoxGlobals {
public:
	static Camera camera;
	static unsigned int width, height;
	static bool idViewPortChanged;
	static bool isOnMenu;
};
