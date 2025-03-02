workspace 'Ronin'
architecture 'ARM64'

configurations {
	'Debug',
	'Release'
}

OutputDir = '%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}'

-- ! Include directories relative to root folder
includeDir = {}
includeDir['GLEW'] = 'ronin/vendor/repos/GLEW/include'
includeDir["GLFW"] = "ronin/vendor/repos/GLFW/include"
includeDir["GLM"] = "ronin/vendor/repos/GLM/"
includeDir["IMGUI"] = "ronin/vendor/repos/ImGUI/"

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

files {
	"%{prj.location}/src/**.h",
	"%{prj.location}/src/**.cpp"
}

defines {
	"_CRT_SECURE_NO_WARNINGS",
	"GLFW_INCLUDE_NONE"
}

includedirs {
	"%{includeDir.GLFW}",
	"%{includeDir.GLEW}",
	"%{includeDir.GLM}",
	"%{includeDir.IMGUI}"
}

links {
	"GLFW",
	"GLEW",
	"IMGUI",
	"Cocoa.framework",
	"OpenGL.framework",
	"IOKit.framework",
}

filter "configurations:Debug"
runtime "Debug"
symbols "On"

filter "configurations:Release"
runtime "Release"
symbols "On"
