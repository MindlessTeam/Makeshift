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

		bool enabled = true;

		void renderIMGUI();

	private: // Values
		// 'ye olde hacky
		bool m_FlagCreation = false;
		float m_TimeSinceFlag = 0;

	private:
		void renderMenuBar();
		void renderViewSettings();
		void renderTextureSettings();
		void renderTexturePreview();
		void renderFileInfoOverlay();

	private:
		void loadPNG();
		void loadResource();

	private:
		std::string m_SourceLocation;
		std::string m_TargetLocation;

		const char* m_CurrentlySelectedTextureFormat = "";
		const char* m_CurrentlySelectedTextureFilteringMode = "";
		const char* m_CurrentlySelectedTextureWrappingMode = "";

	private:
		bool m_ShowTextureSettings;

		// 0 = Full, 1 = R, 2 = G, 3 = B, 4 = A
		int m_ShowTextureChannel = 0;

	private: // Image Stuff
		std::shared_ptr<Makeshift::OpenGL::Texture> m_Texture;
		// A bit inefficient, but I haven't figured out
		// a better way to do it yet.
		std::shared_ptr<Makeshift::OpenGL::Texture> m_ChannelR, m_ChannelG, m_ChannelB, m_ChannelA;

		// Nevermind... this is even more inefficient
		std::vector<unsigned char> m_TextureData, m_RedData, m_BlueData, m_GreenData, m_AlphaData;
		int m_Width, m_Height;

		Makeshift::OpenGL::Texture::TextureFormat m_TextureFormat;
		Makeshift::OpenGL::Texture::TextureFiltering m_TextureFiltering;
		Makeshift::OpenGL::Texture::TextureWrapping m_TextureWrapping;


	};

}