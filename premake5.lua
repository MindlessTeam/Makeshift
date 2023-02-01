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

---------------------------------------------------

project "MakeshiftEngine"
	filename "Engine"
	location "MakeshiftEngine"

	kind "StaticLib"
	language "C++"

	defines { "_CRT_SECURE_NO_WARNINGS" }

	files 
	{
		"src/**.cpp",
		"src/**.hpp",
		"src/**.h",
		"dependencies/**.c",
		"dependencies/**.h",
		"dependencies/**.cpp",
		"dependencies/**.hpp"
	}

	includedirs
	{
		"src",
		"{%wks.location}/dependencies/include"
	}

	libdirs
	{
		"{%wks.location}/dependencies/lib"
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

	pchheader "pch.h"
	pchsource "pch.cpp"

	defines 
	{ 
		"CLIENT",
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
		"{%wks.location}/out/include"
	}

	files 
	{
		"src/**.cpp",
		"src/**.hpp",
		"src/**.h"
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

	defines { "_CRT_SECURE_NO_WARNINGS" }

	includedirs
	{
		"src",
		"{%wks.location}/dependencies/include",
		"{%wks.location}/MakeshiftEngine/src"
	}

	files 
	{
		"src/**.cpp",
		"src/**.hpp",
		"src/**.h"
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

	includedirs
	{
		"src",
		"{%wks.location}/dependencies/include",
		"{%wks.location}/MakeshiftEngine/src"
	}

	files 
	{
		"src/**.cpp",
		"src/**.hpp",
		"src/**.h"
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