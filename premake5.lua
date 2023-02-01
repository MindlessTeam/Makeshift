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
		"MakeshiftClient/src",
		"{%wks.location}/out/include"
	}

	files 
	{
		"MakeshiftClient/src/**.cpp",
		"MakeshiftClient/src/**.hpp",
		"MakeshiftClient/src/**.h"
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
		"MakeshiftApplication/src",
		"{%wks.location}/dependencies/include",
		"{%wks.location}/MakeshiftEngine/src"
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

	includedirs
	{
		"MakeshiftEditor/src",
		"{%wks.location}/dependencies/include",
		"{%wks.location}/MakeshiftEngine/src"
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