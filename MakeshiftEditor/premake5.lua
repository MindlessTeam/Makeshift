project "MakeshiftEditor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.hpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"src",
		"%{wks.location}/dependencies/include",
		"%{wks.location}/Makeshift/src"
	}

	libdirs
	{
		"%{wks.location}/dependencies/lib"
	}

	links
	{
		"Makeshift"
	}
	
	filter "configurations:Debug"
		defines "CFG_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:PreRelease"
		defines "CFG_PRE_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Release"
		defines "CFG_RELEASE"
		runtime "Release"
		optimize "on"