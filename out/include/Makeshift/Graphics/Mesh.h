// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Makeshift/Resource/Resource.h"

#include <vector>
#include <glm/vec3.hpp>

//MAYHAPS:
// Move this to the Resource folder since it is 
// essentially a resource...

namespace Makeshift
{

	// Vertex
	// --------------------------------------------
	// contains all relevant informations about a 
	// vertex.
	struct Vertex
	{
		glm::vec3 position;
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