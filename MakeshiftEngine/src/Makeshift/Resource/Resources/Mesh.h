// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Makeshift/OpenGL/VAO.h"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace Makeshift
{

	// Vertex
	// --------------------------------------
	// Represents a Vertex
	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 UV;
	};

	// Mesh - Resource
	// --------------------------------------
	// A Resource representing a 3D Mesh
	struct Mesh : public Resource
	{

	public:
		std::string getType() override
		{
			return "Mesh";
		}

	public:
		struct Data
		{
			std::shared_ptr<OpenGL::VAO> vao;
			int indexCount;
		};

	public:
		~Mesh() = default;

		Data& getData() { return m_Data; }
		void setData(Data data) { m_Data = data; }

	public:
		// Inherited via Resource
		virtual void loadJson(Json::Value) override;

	private:
		Data m_Data;

	};

}