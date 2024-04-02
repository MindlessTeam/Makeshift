// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift::OpenGL
{

	// Texture
	// ---------------------------------------------
	// A wrapper for an OpenGL texture.
	class Texture
	{

	public:
		enum TextureFormat
		{
			SINGLE_CHANNEL,
			RGB,
			RGBA
		};

		enum TextureType
		{
			TEXTURE_1D,
			TEXTURE_2D,
			TEXTURE_3D
		};

		enum TextureFiltering
		{

		};

	public:
		Texture(const void* data, int width, int height, TextureFormat textureFormat);
		~Texture();

	public:
		// Texture::bind()
		// -----------------------------------------
		// Binds the texture for use.
		void bind() const;
		
		// Texture::unbind()
		// -----------------------------------------
		// Unbinds the texture.
		void unbind() const;

	public:
		// Texture::getRenderID()
		// -----------------------------------------
		// Returns:
		// - The ID the Texture is assigned to.
		unsigned int getRenderID() const { return m_ID; }

	private:
		unsigned int m_ID;

	};

}