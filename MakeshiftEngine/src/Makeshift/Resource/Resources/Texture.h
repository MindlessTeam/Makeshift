// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Makeshift/OpenGL/Texture.h"

#include <memory>

namespace Makeshift
{

	// Texture - Resource
	// --------------------------------------
	// <description>
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
			OpenGL::Texture::TextureFormat textureFormat;
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
		Data m_Data;

	};

}