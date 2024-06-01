// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Texture.h"

#include "Makeshift/Debug/Log.h"

#include <glad/glad.h>

namespace Makeshift::OpenGL
{

	Texture::Texture(const void* data, int width, int height, TextureFormat textureFormat, TextureFiltering textureFiltering, TextureWrapping textureWrapping)
	{
		DEBUG_TRACE("Makeshift::OpenGL::Texture::Texture()");

		glGenTextures(1, &m_ID);

		setTextureFormat(data, width, height, textureFormat, textureFiltering, textureWrapping);
		
		glGenerateMipmap(GL_TEXTURE_2D);

	}

	Texture::~Texture()
	{
		//DEBUG_TRACE("Makeshift::OpenGL::Texture::~Texture()");

		glDeleteTextures(1, &m_ID);
		m_ID = 0;
	}

	void Texture::bind() const
	{
		DEBUG_TRACE("Makeshift::OpenGL::Texture::bind()");

		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture::unbind() const
	{
		DEBUG_TRACE("Makeshift::OpenGL::Texture::unbind()");

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::setTextureFiltering(TextureFiltering textureFiltering)
	{
		DEBUG_TRACE("Makeshift::OpenGL::Texture::setTextureFiltering()");

		bind();

		switch (textureFiltering)
		{
		case TextureFiltering::LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			break;
		case TextureFiltering::NEAREST_NEIGHBOUR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			break;
		}

	}

	void Texture::setTextureWrapping(TextureWrapping textureWrapping)
	{
		DEBUG_TRACE("Makeshift::OpenGL::Texture::setTextureWrapping()");

		bind();

		switch (textureWrapping)
		{
		case TextureWrapping::CLAMP:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			break;
		case TextureWrapping::REPEAT:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case TextureWrapping::REPEAT_REVERSED:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
			break;
		}

	}

	void Texture::setTextureFormat(const void* data, int width, int height, TextureFormat textureFormat, TextureFiltering textureFiltering, TextureWrapping textureWrapping)
	{
		DEBUG_TRACE("Makeshift::OpenGL::Texture::setTextureFormat()");

		glDeleteTextures(1, &m_ID);

		glGenTextures(1, &m_ID);

		bind();

		setTextureFiltering(textureFiltering);
		setTextureWrapping(textureWrapping);

		switch (textureFormat)
		{
		case TextureFormat::SINGLE_CHANNEL:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
			break;
		case TextureFormat::RGB:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			break;
		case TextureFormat::RGBA:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			break;
		}

		glGenerateMipmap(GL_TEXTURE_2D);

	}

}