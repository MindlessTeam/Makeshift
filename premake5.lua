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

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Makeshift"