workspace 'Ronin'
architecture 'ARM64'

configurations {
	'Debug',
	'Release'
}

outputDir = '%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}'

-- ! Include directories relative to root folder
includeDir = {}
includeDir['GLEW'] = 'ronin/vendor/repos/GLEW/include'

project 'Ronin'
location 'ronin'
kind 'ConsoleApp'
language 'C++'
cppdialect 'C++latest'
staticruntime 'on'

targetdir("%{prj.location}/bin/" .. outputDir .. "/%{prj.name}")
objdir("%{prj.location}/bin-int/" .. outputDir .. "/%{prj.name}")

files {
	"%{prj.location}/src/**.h",
	"%{prj.location}/src/**.cpp"
}

defines {
	"_CRT_SECURE_NO_WARNINGS",
}

links {
	"GLEW",
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
