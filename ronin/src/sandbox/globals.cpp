#include "roninpch.h"

#include "sandbox/globals.h"

unsigned int SandBoxGlobals::width = 1080, SandBoxGlobals::height = 720;
bool SandBoxGlobals::idViewPortChanged = false;
Camera SandBoxGlobals::camera = Camera(glm::vec3(0.0f, 0.0f, 60.0f));
bool SandBoxGlobals::isOnMenu = false;
bool SandBoxGlobals::fistMouse = true; // first mouse movement flag

glm::vec4 SandBoxGlobals::lightColor = glm::vec4(1.0, 0.843, 0.130, 1.0);
