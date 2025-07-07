workspace 'Ronin'

configurations {
	'Debug',
	'Release'
}

OutputDir = '%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}'

-- ! Include directories relative to root folder
includeDir = {}
includeDir['GLEW'] = 'ronin/vendor/repos/GLEW/include'
includeDir['GLAD'] = 'ronin/vendor/repos/GLAD/include'
includeDir["GLFW"] = "ronin/vendor/repos/GLFW/include"
includeDir["GLM"] = "ronin/vendor/repos/GLM/"
includeDir["IMGUI"] = "ronin/vendor/repos/ImGUI/"
includeDir["SPDLOG"] = "ronin/vendor/repos/SPDLOG/include"

-- ? This include search for other lua files
include "ronin/vendor/repos/GLFW"
include "ronin/vendor/repos/ImGUI"

project 'Ronin'
location 'ronin'
kind 'ConsoleApp'
language 'C++'
cppdialect 'C++latest'
staticruntime 'on'

targetdir("%{prj.location}/bin/" .. OutputDir .. "/%{prj.name}")
objdir("%{prj.location}/bin-int/" .. OutputDir .. "/%{prj.name}")

pchheader "roninpch.h"
pchsource "%{prj.location}/src/roninpch.cpp"

files {
	"%{prj.location}/src/**.h",
	"%{prj.location}/src/**.cpp",
	"%{prj.location}/res/**/**.glsl",
}

defines {
	"_CRT_SECURE_NO_WARNINGS",
	"GLFW_INCLUDE_NONE"
}

includedirs {
	"%{prj.location}/src/",
	"%{includeDir.GLFW}",
	"%{includeDir.GLEW}",
	"%{includeDir.GLM}",
	"%{includeDir.IMGUI}",
	"%{includeDir.SPDLOG}",
}

filter "system:macosx"
architecture 'ARM64'
systemversion "latest"
links {
	"GLFW",
	"GLEW",
	"IMGUI",
	"Cocoa.framework",
	"OpenGL.framework",
	"IOKit.framework",
}

filter "system:windows"
architecture 'x86_64'
systemversion "latest"
includedirs {
	"%{prj.location}/src/",
	"%{includeDir.GLFW}",
	"%{includeDir.GLAD}",
	"%{includeDir.GLM}",
	"%{includeDir.IMGUI}",
	"%{includeDir.SPDLOG}",
}
links {
	"GLFW",
	"GLAD",
	"IMGUI",
	"opengl32.lib",
}
defines {
	"_CRT_SECURE_NO_WARNINGS",
	"_GLFW_WIN32",
	"GLFW_INCLUDE_NONE",
}
buildoptions { "/utf-8" }
include "ronin/vendor/repos/GLAD"

filter "configurations:Debug"
runtime "Debug"
symbols "On"

filter "configurations:Release"
runtime "Release"
symbols "On"
optimize "on"
