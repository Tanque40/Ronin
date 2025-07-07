#pragma once

#ifdef __APPLE__
#include <GL/glew.h>
#endif

#ifdef _WIN32
#include <Windows.h>
#include <glad/glad.h>
#endif

#include <GLFW/glfw3.h>

#include <string>
#include <cstdint>

#include <unordered_map>

#include <fstream>
#include <iostream>

#include <vector>

#include <spdlog/spdlog.h>
