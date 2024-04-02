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

	std::vector<unsigned char> Texture::loadTextureData(const std::string location)
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

}