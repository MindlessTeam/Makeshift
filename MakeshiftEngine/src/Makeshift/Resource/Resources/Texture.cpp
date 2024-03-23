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

namespace Makeshift
{

	void Texture::loadJson(Json::Value root)
	{
		DEBUG_TRACE("Makeshift::Texture::loadJson()");

		m_Data.width = root["Width"].asInt();
		m_Data.height = root["Height"].asInt();

		std::vector<unsigned char> imageData;
		
		const Json::Value& JSONimageData = root["Image Data"];
		for (const auto& byte : JSONimageData)
		{
			imageData.push_back(byte.asUInt());
		}
		
		//TODO: Image Settings

		

		m_Data.texture = std::make_shared<OpenGL::Texture>(imageData.data(), m_Data.width, m_Data.height, OpenGL::Texture::TextureFormat::RGB);

	}

}