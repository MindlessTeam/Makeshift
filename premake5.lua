workspace "Project"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"PreRelease",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

	startproject "MakeshiftTest"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Makeshift"
include "MakeshiftTest"