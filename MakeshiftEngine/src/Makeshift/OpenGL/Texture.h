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
			LINEAR,
			NEAREST_NEIGHBOUR
		};

		enum TextureWrapping
		{
			REPEAT,
			REPEAT_REVERSED,
			CLAMP
		};

	public:
		Texture(const void* data, 
			int width, 
			int height, 
			TextureFormat textureFormat = TextureFormat::RGB,
			TextureFiltering textureFiltering = TextureFiltering::LINEAR,
			TextureWrapping textureWrapping = TextureWrapping::REPEAT);
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
		// Texture::setTextureFiltering()
		// -----------------------------------------
		// Changes the texture filtering of the texture.
		// 
		//Parameters:
		// - textureFiltering: the target texture filtering mode
		void setTextureFiltering(TextureFiltering textureFiltering = TextureFiltering::LINEAR);

		// Texture::setTextureWrapping()
		// Changes the texture wrapping of the texture.
		// 
		//Parameters:
		// - textureWrapping: the target texture wrapping mode
		void setTextureWrapping(TextureWrapping textureWrapping = TextureWrapping::REPEAT);

		// Texture::setTextureFormat()
		// Changes the texture format of the texture.
		// 
		//Parameters:
		// - data: the image data
		// - textureFormat: the target texture format
		//
		//NOTE: This recreates the OpenGL texture object. Any changes to filtering and wrapping will have to be reapplied!
		void setTextureFormat(const void* data, 
			int width, 
			int height,
			TextureFormat textureFormat = TextureFormat::RGB, 
			TextureFiltering textureFiltering = TextureFiltering::LINEAR,
			TextureWrapping textureWrapping = TextureWrapping::REPEAT);

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