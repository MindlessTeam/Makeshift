// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Makeshift/OpenGL/Texture.h"

#include <memory>
#include <vector>

#include <glm/vec4.hpp>

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
			OpenGL::Texture::TextureWrapping textureWrapping;
		};

	public:
		~Texture() = default;

		Data& getData() { return m_Data; }
		void setData(Data data) { m_Data = data; }

	public:
		// Inherited via Resource
		virtual void loadJson(Json::Value) override;

		virtual void loadDefaultValues() override;
		
	public:
		// Texture::save()
		// -----------------------------------------
		// Saves a Texture.
		//
		// Parameters:
		// - location: the location to write to
		// - imageData: the raw image Data
		// - width: the width of the image
		// - height: the height of the image
		// - textureType: the type of texture
		// - textureFormat: the format of the texture
		// - textureFiltering: the filtering setting
		// - textureWrapping: the wrapping setting
		static void save(const std::string& location,
			std::vector<unsigned char>& imageData,
			int width,
			int height,
			OpenGL::Texture::TextureType textureType = OpenGL::Texture::TextureType::TEXTURE_2D,
			OpenGL::Texture::TextureFormat textureFormat = OpenGL::Texture::TextureFormat::RGBA,
			OpenGL::Texture::TextureFiltering textureFiltering = OpenGL::Texture::TextureFiltering::LINEAR,
			OpenGL::Texture::TextureWrapping textureWrapping = OpenGL::Texture::TextureWrapping::REPEAT);

		// Texture::loadImageData()
		// -----------------------------------------
		// Loads an image file.
		// 
		// Parameters:
		// - location: the file location (.png)
		// - out width: width of the image
		// - out height: height of the image
		// - out textureFormat: format of the image
		//
		// Returns:
		// - a vector of unsigned char representing the bytes of the image data
		static std::vector<unsigned char> loadImageData(const std::string& location, int& width, int& height, OpenGL::Texture::TextureFormat& textureFormat);

		// Texture::createCheckerTexture()
		// -----------------------------------------
		// Creates a square pixel-by-pixel checkerboard
		// texture.
		//
		// Parameters:
		// - resolution: the resolution (x and y) of the texture to create
		// - colourA: the first colour in the checkerboard
		// - colourB: the second colour making up the checkerboard
		//
		// Returns:
		// - a vector of unsigned char representing the bytes of the image data (in RGBA format)
		static std::vector<unsigned char> createCheckerTexture(int resolution, glm::vec4 colourA = glm::vec4(255, 255, 255, 255), glm::vec4 colourB = glm::vec4(0, 0, 0, 0));

		// Texture::splitImageDataIntoChannels()
		// -----------------------------------------
		// Splits a multi-channel image into its
		// make-up.
		//
		// Parameters:
		// - completeData: the data of the multi-channel image
		// - format: the format to decompile
		// - out redData: the first channels data
		// - out greenData: the second channels data (if applicable)
		// - out blueData: the third channels data (if applicable)
		// - out alphaData: the fourth channels data (if applicable)
		static void splitImageDataIntoChannels(std::vector<unsigned char>& completeData, OpenGL::Texture::TextureFormat format, std::vector<unsigned char>& redData, std::vector<unsigned char>& greenData, std::vector<unsigned char>& blueData, std::vector<unsigned char>& alphaData);

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
		static std::vector<unsigned char> loadTextureData(const std::string& location);

		// Texture::saveTextureData()
		// -----------------------------------------
		// Saves an images raw binary data.
		//
		// Parameters:
		// - imageData: the data to save
		// - location: the location to write to
		static void saveTextureData(const std::string& location, std::vector<unsigned char>& imageData);

	private:
		Data m_Data;

	};

}