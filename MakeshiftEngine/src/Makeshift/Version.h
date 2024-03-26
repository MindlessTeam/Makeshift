#pragma once

#define VERSION_MAJOR 0 // Major Features / Milestones
#define VERSION_MINOR 0 // Features
#define VERSION_PATCH 1 // Bug-Fixes / Patches

// Version
// -----------------------------------------
// A Utility class that implements a nicer
// way of working with Versions.
struct Version
{

	// If you create an Empty Version Object, it will have the current Engine Version
	int major = VERSION_MAJOR;
	int minor = VERSION_MINOR;
	int patch = VERSION_PATCH;

	Version() {}
	Version(int major, int minor, int patch) : major(major), minor(minor), patch(patch) {}
	Version(const Version& other) : major(other.major), minor(other.minor), patch(other.patch) {}

	Version& operator=(const Version& other)
	{
		if (this != &other)
		{
			major = other.major;
			minor = other.minor;
			patch = other.patch;
		}
		return *this;
	}

	bool operator==(const Version& other) const
	{
		return major == other.major && minor == other.minor && patch == other.patch;
	}

	bool operator!=(const Version& other) const
	{
		return !(*this == other);
	}

	bool operator<(const Version& other) const
	{
		if (major != other.major)
			return major < other.major;
		if (minor != other.minor)
			return minor < other.minor;
		return patch < other.patch;
	}

	bool operator>(const Version& other) const
	{
		return other < *this;
	}

	bool operator<=(const Version& other) const
	{
		return !(other < *this);
	}

	bool operator>=(const Version& other) const
	{
		return !(*this < other);
	}

};