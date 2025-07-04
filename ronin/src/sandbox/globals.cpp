#include "sandbox/globals.h"

unsigned int SandBoxGlobals::width = 1080, SandBoxGlobals::height = 720;
bool SandBoxGlobals::idViewPortChanged = false;
Camera SandBoxGlobals::camera = Camera(glm::vec3(0.0f, 0.0f, 10.0f));
bool SandBoxGlobals::isOnMenu = true;
