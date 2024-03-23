// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>
#include <vector>

#include <Makeshift/Resource/Resources/Texture.h>

namespace MakeshiftEditor
{

	struct TextureCreator
	{

		bool enabled = false;

		void renderIMGUI();

	private:
		//void saveTextureToDisk(const std::string& location);

	private: // Values
		std::vector<unsigned char> m_ImageData;
		int m_ImageWidth;
		int m_ImageHeight;

		std::string m_TextureOrigin;
		std::string m_TextureDestination;

		std::vector<std::shared_ptr<Makeshift::Texture>> m_Textures;

		bool m_AvailableTexture = false;

	};

}