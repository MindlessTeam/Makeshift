// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Makeshift/OpenGL/Texture.h"

#include <memory>
#include <vector>

namespace Makeshift
{

	// Texture - Resource
	// ---------------------------------------------
	// A Texture Resource. Represents an image in 
	// Makeshift.
	struct Texture : public Resource
	{

	public:
		std::string getType() override
		{
			return "Texture";
		}

	public:
		struct Data
		{
			std::shared_ptr<OpenGL::Texture> texture;
			int width, height;
			OpenGL::Texture::TextureFormat textureFormat; // To be removed
			OpenGL::Texture::TextureType textureType;
			OpenGL::Texture::TextureFiltering textureFiltering;
		};

	public:
		~Texture() = default;

		Data& getData() { return m_Data; }
		void setData(Data data) { m_Data = data; }

	public:
		// Inherited via Resource
		virtual void loadJson(Json::Value) override;

	private:
		// Texture::loadTextureData()
		// -----------------------------------------
		// Loads an images raw binary data.
		//
		// Parameters:
		// - location: the file location (accepts any file type (in theory))
		//
		// Returns:
		// - a vector of unsigned char representing the bytes of the image data
		std::vector<unsigned char> loadTextureData(const std::string location);

	private:
		Data m_Data;

	};

}