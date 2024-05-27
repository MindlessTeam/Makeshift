// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Texture.h"

#include "Makeshift/Debug/Log.h"

#include "Makeshift/Version.h"

#include <json/json.h>

#include <imgui/imgui.h>

#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Makeshift
{

	void Texture::loadJson(Json::Value root)
	{
		DEBUG_TRACE("Makeshift::Texture::loadJson()");

		m_Data.width = root["Width"].asInt();
		m_Data.height = root["Height"].asInt();

		std::vector<unsigned char> imageData = loadTextureData(root["Image Data"].asString());
		
		//TODO: Image Settings

		

		m_Data.texture = std::make_shared<OpenGL::Texture>(imageData.data(), m_Data.width, m_Data.height, OpenGL::Texture::TextureFormat::RGB);

	}

	void Texture::loadDefaultValues()
	{

		m_Data.width = 16;
		m_Data.height = 16;
		
		m_Data.textureType = OpenGL::Texture::TEXTURE_2D;
		m_Data.textureWrapping = OpenGL::Texture::REPEAT;
		m_Data.textureFormat = OpenGL::Texture::RGBA;
		m_Data.textureFiltering = OpenGL::Texture::LINEAR;

		//TODO: Default Image Data

		

	}

	void Texture::save(const std::string& location, std::vector<unsigned char>& imageData, int width, int height, OpenGL::Texture::TextureType textureType, OpenGL::Texture::TextureFormat textureFormat, OpenGL::Texture::TextureFiltering textureFiltering, OpenGL::Texture::TextureWrapping textureWrapping)
	{

		Json::Value root;

		root["Type"] = "Texture";
		root["Version"]["major"] = VERSION_MAJOR;
		root["Version"]["minor"] = VERSION_MINOR;
		root["Version"]["patch"] = VERSION_PATCH;

		std::string textureDataLocation(location + ".data");
		saveTextureData(textureDataLocation, imageData);

		root["Width"] = width;
		root["Height"] = height;

		Json::Value settings;

		switch (textureType)
		{
		case OpenGL::Texture::TEXTURE_1D:
			settings["Type"] = 1;
			break;
		case OpenGL::Texture::TEXTURE_2D:
			settings["Type"] = 2;
			break;
		case OpenGL::Texture::TEXTURE_3D:
			settings["Type"] = 3;
			break;
		}

		switch (textureFormat)
		{
		case OpenGL::Texture::SINGLE_CHANNEL:
			settings["Format"] = 1;
			break;
		case OpenGL::Texture::RGB:
			settings["Format"] = 2;
			break;
		case OpenGL::Texture::RGBA:
			settings["Format"] = 3;
			break;
		}

		switch (textureFiltering)
		{
		case OpenGL::Texture::LINEAR:
			settings["Filtering"] = 1;
			break;
		case OpenGL::Texture::NEAREST_NEIGHBOUR:
			settings["Filtering"] = 2;
			break;
		}

		switch (textureWrapping)
		{
		case OpenGL::Texture::REPEAT:
			settings["Wrapping"] = 1;
			break;
		case OpenGL::Texture::REPEAT_REVERSED:
			settings["Wrapping"] = 2;
			break;
		case OpenGL::Texture::CLAMP:
			settings["Wrapping"] = 3;
			break;
		}

		root["Texture Settings"] = settings;

		std::ofstream file(location);
		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to open file '{}' for writing!", location);
			file.close();
			return;
		}

		Json::StyledWriter writer;
		file << writer.write(root);
		file.close();

	}

	std::vector<unsigned char> Texture::loadImageData(const std::string& location, int& width, int& height, OpenGL::Texture::TextureFormat& textureFormat)
	{
		
		int channels;

		unsigned char* imageData = stbi_load(location.c_str(), &width, &height, &channels, 0);

		if (!imageData)
		{
			DEBUG_ERROR("Failed to load .png file '{}' - check for supported file-types!", location);
		}

		switch (channels)
		{
		case 1:
			textureFormat = OpenGL::Texture::TextureFormat::SINGLE_CHANNEL;
			break;
		case 3:
			textureFormat = OpenGL::Texture::TextureFormat::RGB;
			break;
		case 4:
			textureFormat = OpenGL::Texture::TextureFormat::RGBA;
			break;
		default:
			DEBUG_ERROR("Unsupported file format encountered while loading file '{}'!", location);
			break;
		}

		return std::vector<unsigned char>();

	}

	std::vector<unsigned char> Texture::createCheckerTexture(int resolution, glm::vec4 colourA, glm::vec4 colourB)
	{
		
		return std::vector<unsigned char>();

	}

	std::vector<unsigned char> Texture::loadTextureData(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Texture::loadTextureData()");
		
		std::vector<unsigned char> imageData;

		// Open the file
		std::ifstream file(location, std::ios::in | std::ios::binary);

		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to load texture Data from location '{}'", location);
			return imageData; //TODO: Defaults! (i.e. return a black/pink checker)
		}

		int vectorSize;
		file.read(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));

		imageData.resize(vectorSize);
		file.read(reinterpret_cast<char*>(imageData.data()), vectorSize);

		// Stop reading
		file.close();

		// Return the loaded data
		return imageData;
	}

	void Texture::saveTextureData(const std::string& location, std::vector<unsigned char>& imageData)
	{

		std::ofstream file(location, std::ios::out | std::ios::binary);

		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to open file '{}' for writing!", location);
			file.close();
			return;
		}

		int vectorSize = imageData.size();

		file.write(reinterpret_cast<char*>(&vectorSize), sizeof(vectorSize));
		file.write(reinterpret_cast<char*>(imageData.data()), vectorSize);

		file.close();

	}

}