project "Makeshift"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/out/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/out/obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp",
		"src/**.hpp",
		"dependencies/**.c",
		"dependencies/**.h",
		"dependencies/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	libdirs
	{
		"%{wks.location}/dependencies/lib"
	}

	includedirs
	{
		"src",
		"%{wks.location}/dependencies/include",
		"%{wks.location}/dependencies/include/imgui"
	}

	links
	{
		"glfw3.lib",
		"opengl32.lib"
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