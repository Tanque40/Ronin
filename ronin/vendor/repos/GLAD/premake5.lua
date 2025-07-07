project "GLAD"
kind "StaticLib"
architecture 'x86_64'
language "C"
staticruntime "on"

targetdir("bin/" .. OutputDir .. "/%{prj.name}")
objdir("bin-int/" .. OutputDir .. "/%{prj.name}")

files
{
	"include/glad/glad.h",
	"include/KHR/khrplatform.h",
	"src/glad.c",
}

includedirs {
	"include"
}

filter "system:windows"
systemversion "latest"

filter "configurations:Debug"
runtime "Debug"
symbols "on"

filter "configurations:Release"
runtime "Release"
optimize "on"
