// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Makeshift/OpenGL/VAO.h"

#include <glm/vec3.hpp>
#include <vector>

namespace Makeshift
{

	struct Vertex
	{
		glm::vec3 position;
	};

	// Mesh - Resource
	// --------------------------------------
	// <description>
	struct Mesh : public Resource
	{

	public:
		struct Data
		{
			std::vector<Vertex> vertices;
			std::vector<uint32_t> indices;
			VAO vao;
		};

	public:
		~Mesh() = default;

		Data& getData() { return m_Data; }
#ifdef EDITOR
		void setData(Data data) { m_Data = data; }
#endif

	public:
		// Inherited via Resource
		virtual void load(const std::string& location) override;

#ifdef EDITOR
		virtual void renderIMGUI() override
		{
			ImGui::Text(std::to_string(m_Data.vertices.size()).c_str());
			ImGui::Text(std::to_string(m_Data.indices.size()).c_str());
		}
#endif

	private:
		Data m_Data;

	};

}