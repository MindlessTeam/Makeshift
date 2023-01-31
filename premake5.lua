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

	startproject "MakeshiftEditor"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Makeshift"
include "MakeshiftTest"
include "MakeshiftEditor"