// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Resource.h"

#include <glm/vec3.hpp>

#include <vector>

#ifdef EDITOR
#include <imgui/imgui.h>
#endif

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
			ImGui::Text(std::to_string(m_Data.vertices.size().c_str()));
			ImGui::Text(std::to_string(m_Data.indices.size().c_str());
		}
		#endif

	private:
		Data m_Data;



	};

}