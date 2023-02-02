// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Resource.h"

#include <glm/vec3.hpp>

#include <vector>

namespace Makeshift
{

	// Vertex
	// -----------------------------------------
	// Contains vertex data
	struct Vertex
	{
		glm::vec3 position;
	};

	// Mesh - Resource
	// -----------------------------------------
	// Represents a 3d model
	struct Mesh : public Resource
	{

	public:
		struct Data
		{
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
		};
	public:
		Mesh(std::vector<Vertex>& vertices, std::vector<uint32_t> indices)
		{
			m_Data.vertices = vertices;
			m_Data.indices = indices;
		}
		Mesh(Data& data) 
		{
			m_Data = data;
		}
		~Mesh() = default;

		Data& getData() { return m_Data; }

	private:
		Data m_Data;

	};

}