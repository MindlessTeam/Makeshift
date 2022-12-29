// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Resource.h"

#include <vector>
#include <glm/vec3.hpp>

namespace Makeshift
{

	// Vertex
	// --------------------------------------------
	// contains all relevant informations about a 
	// vertex.
	struct Vertex
	{
		glm::vec3 position; // Will expand...!
	};

	// Mesh
	// --------------------------------------------
	// A resource that contains model data.
	class Mesh : public Resource
	{

	public:
		struct Data : Resource::Data
		{
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
		};

	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
		{
			m_Data.vertices = vertices;
			m_Data.indices = indices;
		}

		Data& getData() override
		{
			return m_Data;
		}

	private:
		Data m_Data;

	};

}