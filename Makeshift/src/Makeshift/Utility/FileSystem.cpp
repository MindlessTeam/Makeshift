// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "FileSystem.h"

#include "Makeshift/Debug/Log.h"

#include <fstream>
#include <sstream>
#include <strstream>

#include <unordered_map>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <glm/gtx/hash.hpp>

namespace Makeshift
{
	namespace Util
	{

		std::string& FileLocations::contentLocation()
		{
			static std::string cLoc = "content";
			return cLoc;
		}

		std::string& FileLocations::modelLocation()
		{
			static std::string mLoc = "content/mdl";
			return mLoc;
		}

		std::string& FileLocations::logLocation()
		{
			static std::string lLoc = "log";
			return lLoc;
		}


		// See StackOverflow:
		// https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
		bool FileSystem::dirExist(const std::string& path)
		{
			DEBUG_TRACE("Makeshift::Util::FileSystem::dirExist()");

			DEBUG_INFO("Checking if directory {} exists...", path);
			struct stat buffer;
			return(stat(path.c_str(), &buffer) == 0);

		}

		std::string FileSystem::loadRawText(const std::string& path)
		{
			DEBUG_TRACE("Makeshift::Util::FileSystem::loadRawText()");

			DEBUG_INFO("Loading file {}...", path);
			std::ifstream input(path, std::ios::in | std::ios::binary);
			if (input)
			{
				std::string content;

				input.seekg(0, std::ios::end);
				content.resize(input.tellg());
				input.seekg(0, std::ios::beg);
				input.read(&content[0], content.size());
				input.close();

				return(content);
			}

			DEBUG_ERROR("Failed to load {}!", path);

		}

		Mesh FileSystem::loadRawMesh(const std::string& path)
		{
			DEBUG_TRACE("Makeshift::Util::FileSystem::loadRawMesh()");

			DEBUG_INFO("Loading obj file {}.obj...", path);
			std::istringstream sourceStream(loadRawText(path + ".obj"));

			tinyobj::attrib_t attributes;
			std::vector<tinyobj::shape_t> shapes;
			std::vector<tinyobj::material_t> materials;

			std::string errors;

			if (!tinyobj::LoadObj
			(
				&attributes,
				&shapes,
				&materials,
				&errors,
				&sourceStream
			))
			{
				DEBUG_ERROR("Failed to load {}.obj! - {}", path, errors);
			}

			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
			std::unordered_map<glm::vec3, uint32_t> uniqueVertices;

			for (const auto& shape : shapes)
			{
				for (const auto& index : shape.mesh.indices)
				{
					glm::vec3 position
					{
						attributes.vertices[3 * index.vertex_index + 0],
						attributes.vertices[3 * index.vertex_index + 1],
						attributes.vertices[3 * index.vertex_index + 2]
					};

					if (uniqueVertices.count(position) == 0)
					{
						uniqueVertices[position] = static_cast<uint32_t>(vertices.size());
						vertices.push_back(Vertex{ position });
					}

					indices.push_back(uniqueVertices[position]);
				}
			}

			return Mesh{ vertices, indices };
			
		}

		Mesh FileSystem::loadMesh(const std::string& path)
		{
			DEBUG_TRACE("Makeshift::Util::FileSystem::loadMesh()");
			
			DEBUG_INFO("Loading model definition file {}.mdef...", path);
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices; // Does this cause a memory leak?

			std::ifstream input(path + ".mdef", std::ios::in | std::ios::binary);
			if(input)
			{
				int vertexCount;
				int indexCount;

				input.read(reinterpret_cast<char*>(&vertexCount), sizeof(vertexCount));
				input.read(reinterpret_cast<char*>(&indexCount), sizeof(vertexCount));
				vertices.resize(vertexCount);
				indices.resize(indexCount);

				input.read(reinterpret_cast<char*>(&vertices[0]), sizeof(glm::vec3) * vertexCount);
				input.read(reinterpret_cast<char*>(&indices[0]), sizeof(uint32_t) * indexCount);
			}
			else
			{
				DEBUG_ERROR("Failed to load {}.mdef!", path);
			}

			return Mesh{ vertices, indices };

		}

		void FileSystem::exportMesh(Mesh mesh, std::string path)
		{
			DEBUG_TRACE("Makeshift::Util::FileSystem::exportMesh()");

			DEBUG_INFO("Exporting model definition file {}.mdef", path);
			std::ofstream output(path + ".mdef", std::ios::out | std::ios::binary);
			if (output)
			{
				Mesh::Data meshData = mesh.getData();

				int vertexCount = meshData.vertices.size();
				int indexCount = meshData.indices.size();

				// Here we are taking advantage of the fact that we know what data is supposed to be read in what order
				// First we tell the file how many vertices there are,
				// then how many indices.
				output.write(reinterpret_cast<const char*>(&vertexCount), sizeof(vertexCount));
				output.write(reinterpret_cast<const char*>(&indexCount), sizeof(indexCount));

				// We then export the vectors...
				// When reading the file we know exactly how much data we need to read in, because
				// we told the file how large the arrays are.
				output.write(reinterpret_cast<const char*>(&meshData.vertices[0]), sizeof(glm::vec3) * vertexCount);
				output.write(reinterpret_cast<const char*>(&meshData.indices[0]), sizeof(uint32_t) * indexCount);

				output.close();
			}
			else
			{
				DEBUG_ERROR("Failed to open {}.mdef for writing!", path);
			}

		}

	}
}