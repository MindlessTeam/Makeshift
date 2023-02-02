workspace "MakeshiftSDK"
-- Put that SDK in huge quotations 
	architecture "x86_64"

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

project "MakeshiftEngine"
	filename "Engine"
	location "MakeshiftEngine"

	kind "StaticLib"
	language "C++"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")

	defines { "_CRT_SECURE_NO_WARNINGS" }

	files 
	{
		"MakeshiftEngine/src/**.cpp",
		"MakeshiftEngine/src/**.hpp",
		"MakeshiftEngine/src/**.h",
		"MakeshiftEngine/dependencies/**.c",
		"MakeshiftEngine/dependencies/**.h",
		"MakeshiftEngine/dependencies/**.cpp",
		"MakeshiftEngine/dependencies/**.hpp"
	}

	includedirs
	{
		"MakeshiftEngine/src",
		"%{wks.location}/dependencies/include",
		"%{wks.location}/dependencies/include/imgui"
	}

	libdirs
	{
		"%{wks.location}/dependencies/lib"
	}

	links
	{
		"opengl32",
		"glfw3.lib"
	}

	filter "configurations:Debug"
		defines { "CFG_DEBUG" }
		symbols "On"
		optimize "Off"
	
	filter "configurations:PreRelease"
		defines { "CFG_PRERELEASE" }
		
	filter "configurations:Release"
		defines { "CFG_RELEASE" }
		optimize "On"

---------------------------------------------------

project "MakeshiftClient"
	filename "Client"
	location "MakeshiftClient"

	kind "SharedLib"
	language "C++"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")

	defines 
	{ 
		"CLIENT",
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"MakeshiftClient/src",
		"%{wks.location}/MakeshiftEngine/src"
	}

	files 
	{
		"MakeshiftClient/src/**.cpp",
		"MakeshiftClient/src/**.hpp",
		"MakeshiftClient/src/**.h"
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
		
	filter "configurations:Release"
		defines { "CFG_RELEASE" }
		optimize "On"

---------------------------------------------------

project "MakeshiftApplication"
	filename "App"
	location "MakeshiftApplication"
	
	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")

	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs
	{
		"MakeshiftApplication/src",
		"%{wks.location}/dependencies/include",
		"%{wks.location}/MakeshiftEngine/src",
		"%{wks.location}/MakeshiftClient/src" -- this is temporary
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
		
	filter "configurations:Release"
		defines { "CFG_RELEASE" }
		optimize "On"

---------------------------------------------------

project "MakeshiftEditor"
	filename "Editor"
	location "MakeshiftEditor"
	
	kind "ConsoleApp"
	language "C++"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")

	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs
	{
		"MakeshiftEditor/src",
		"%{wks.location}/dependencies/include",
		"%{wks.location}/MakeshiftEngine/src",
		"%{wks.location}/MakeshiftClient/src" -- this is temporary as well
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
		
	filter "configurations:Release"
		defines { "CFG_RELEASE" }
		optimize "On"