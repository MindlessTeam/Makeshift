// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>
#include <vector>
#include <memory>

#include <Makeshift/OpenGL/Texture.h>

namespace MakeshiftEditor
{

	struct TextureEditor
	{

		bool enabled = false;

		void renderIMGUI();

	private: // Values
		// 'ye olde hacky
		bool m_FlagCreation = false;
		float m_TimeSinceFlag = 0;

	private:
		std::string m_PNGLocation;
		std::string m_ResourceLocation; //TODO:

	private:
		bool m_ShowTextureSettings;

		// 0 = Full, 1 = R, 2 = G, 3 = B, 4 = A
		int m_TextureChannel = 0;

	private: // Image Stuff
		std::shared_ptr<Makeshift::OpenGL::Texture> m_Texture;
		// A bit inefficient, but I haven't figured out
		// a better way to do it yet.
		std::shared_ptr<Makeshift::OpenGL::Texture> m_ChannelR, m_ChannelG, m_ChannelB, m_ChannelA;

	};

}