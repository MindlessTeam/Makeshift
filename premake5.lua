workspace "MakeshiftSDK"
-- Put that SDK in huge quotations 
	architecture "x86_64"
	cppdialect "C++17"

	configurations 
	{ 
		"Debug",
		"PreRelease",
		"Release" 
	}

	flags { "MultiProcessorCompile" }

	startproject "MakeshiftApplication"

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

---------------------------------------------------

group "Dependencies"
	include "dependencies/imgui/imgui"
	include "dependencies/jsoncpp"
	include "dependencies/spdlog"
	include "dependencies/glad"
	include "dependencies/GLFW"
group ""

---------------------------------------------------

group "Core"
project "MakeshiftEngine"
	filename "Engine"
	location "MakeshiftEngine"

	kind "StaticLib"
	language "C++"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")
	debugdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")

	defines { "_CRT_SECURE_NO_WARNINGS" }

	files 
	{
		"MakeshiftEngine/src/**.cpp",
		"MakeshiftEngine/src/**.hpp",
		"MakeshiftEngine/src/**.h"
	}

	includedirs
	{
		"MakeshiftEngine/src",
		"%{wks.location}/dependencies/glad/include",
		"%{wks.location}/dependencies/imgui",
		"%{wks.location}/dependencies/imgui/imgui",
		"%{wks.location}/dependencies/glm",
		"%{wks.location}/dependencies/glfw/include",
		"%{wks.location}/dependencies/IconFontCppHeaders",
		"%{wks.location}/dependencies/jsoncpp/include",
		"%{wks.location}/dependencies/spdlog/include",
		"%{wks.location}/dependencies/tinyobjloader/include",
		"%{wks.location}/dependencies/stb"
	}

	libdirs
	{
		"%{wks.location}/dependencies/freetype/release static/vs2015-2022/win64"
	}

	links
	{
		"opengl32",
		"freetype.lib",
		"ImGui",
		"Json",
		"spdlog",
		"Glad",
		"GLFW"
	}

	prebuildcommands
	{
		"../scripts/generateIncludes.bat"
	}

	postbuildcommands
	{
		"../scripts/copyContent.bat"
	}

	filter "configurations:Debug"
		defines { "CFG_DEBUG" }
		symbols "On"
		optimize "Off"
	
	filter "configurations:PreRelease"
		defines { "CFG_PRERELEASE" }
		symbols "On"
		optimize "On"
		
	filter "configurations:Release"
		defines { "CFG_RELEASE" }
		symbols "Off"
		optimize "On"

---------------------------------------------------

group ""
project "MakeshiftClient"
	filename "Client"
	location "MakeshiftClient"

	kind "SharedLib"
	language "C++"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")
	debugdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")

	defines 
	{ 
		"CLIENT",
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"MakeshiftClient/src",
		"%{wks.location}/dependencies/glad/include",
		"%{wks.location}/dependencies/imgui",
		"%{wks.location}/dependencies/glm",
		"%{wks.location}/dependencies/glfw/include",
		"%{wks.location}/dependencies/IconFontCppHeaders",
		"%{wks.location}/dependencies/jsoncpp/include",
		"%{wks.location}/dependencies/spdlog/include",
		"%{wks.location}/dependencies/tinyobjloader/include",
		"%{wks.location}/dependencies/stb",
		"%{wks.location}/MakeshiftEngine/src"
	}

	files 
	{
		"MakeshiftClient/src/**.cpp",
		"MakeshiftClient/src/**.hpp",
		"MakeshiftClient/src/**.h"
	}

	links
	{
		"MakeshiftEngine"
	}
	
	postbuildcommands
	{
		"{COPYDIR} ../out/bin/" .. outputdir .. "/MakeshiftClient/  ../out/bin/" .. outputdir .. "/MakeshiftApplication/",
		"{COPYDIR} ../out/bin/" .. outputdir .. "/MakeshiftClient/  ../out/bin/" .. outputdir .. "/MakeshiftEditor/"
	}

	filter "configurations:Debug"
		defines { "CFG_DEBUG" }
		symbols "On"
		optimize "Off"
	
	filter "configurations:PreRelease"
		defines { "CFG_PRERELEASE" }
		symbols "On"
		optimize "On"
		
	filter "configurations:Release"
		defines { "CFG_RELEASE" }
		symbols "Off"
		optimize "On"

---------------------------------------------------

group "Core"
project "MakeshiftApplication"
	filename "App"
	location "MakeshiftApplication"
	
	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")
	debugdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")

	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs
	{
		"MakeshiftApplication/src",
		"%{wks.location}/dependencies/glad",
		"%{wks.location}/dependencies/imgui",
		"%{wks.location}/dependencies/glm",
		"%{wks.location}/dependencies/glfw/include",
		"%{wks.location}/dependencies/IconFontCppHeaders",
		"%{wks.location}/dependencies/jsoncpp/include",
		"%{wks.location}/dependencies/spdlog/include",
		"%{wks.location}/dependencies/tinyobjloader/include",
		"%{wks.location}/dependencies/stb",
		"%{wks.location}/MakeshiftClient/src",
		"%{wks.location}/MakeshiftEngine/src"
	}

	files 
	{
		"MakeshiftApplication/src/**.cpp",
		"MakeshiftApplication/src/**.hpp",
		"MakeshiftApplication/src/**.h"
	}

	links
	{
		"MakeshiftEngine",
		"MakeshiftClient"
	}

	filter "configurations:Debug"
		defines { "CFG_DEBUG" }
		symbols "On"
		optimize "Off"
	
	filter "configurations:PreRelease"
		defines { "CFG_PRERELEASE" }
		symbols "On"
		optimize "On"
		
	filter "configurations:Release"
		defines { "CFG_RELEASE" }
		symbols "Off"
		optimize "On"

---------------------------------------------------

project "MakeshiftEditor"
	filename "Editor"
	location "MakeshiftEditor"
	
	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")
	debugdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")

	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs
	{
		"MakeshiftEditor/src",
		"%{wks.location}/dependencies/glad",
		"%{wks.location}/dependencies/imgui",
		"%{wks.location}/dependencies/glm",
		"%{wks.location}/dependencies/glfw/include",
		"%{wks.location}/dependencies/IconFontCppHeaders",
		"%{wks.location}/dependencies/jsoncpp/include",
		"%{wks.location}/dependencies/spdlog/include",
		"%{wks.location}/dependencies/tinyobjloader/include",
		"%{wks.location}/dependencies/stb",
		"%{wks.location}/MakeshiftClient/src",
		"%{wks.location}/MakeshiftEngine/src"
	}

	files 
	{
		"MakeshiftEditor/src/**.cpp",
		"MakeshiftEditor/src/**.hpp",
		"MakeshiftEditor/src/**.h"
	}

	links
	{
		"MakeshiftEngine",
		"MakeshiftClient"
	}

	filter "configurations:Debug"
		defines { "CFG_DEBUG" }
		symbols "On"
		optimize "Off"
	
	filter "configurations:PreRelease"
		defines { "CFG_PRERELEASE" }
		symbols "On"
		optimize "On"
		
	filter "configurations:Release"
		defines { "CFG_RELEASE" }
		symbols "Off"
		optimize "On"

group ""