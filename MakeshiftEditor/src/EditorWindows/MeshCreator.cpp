// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "MeshCreator.h"

#include "Explorer.h"

#include <Makeshift/Debug/Log.h>

#include <imgui/imgui.h>
#include <imgui/imgui_stdlib.h>

#include <json/json.h>

#include <fstream>

#include <glm/gtx/hash.hpp>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace MakeshiftEditor
{

	void MeshCreator::renderIMGUI()
	{

		if (enabled)
		{

			ImGui::Begin("Mesh Creator");

			ImGui::InputText("Mesh Source Location", &m_OBJSourceLocation);
			ImGui::SameLine();
			if (ImGui::Button("Mesh Source Explore"))
			{
				m_OBJSourceLocation = Explorer::getFilePath();
			}

			ImGui::InputText("Mesh Location", &m_Location);
			ImGui::SameLine();
			if (ImGui::Button("Mesh Explore"))
			{
				m_Location = Explorer::getRelativeCreatedFilePath();
			}

			if (ImGui::Button("Create Mesh"))
			{
				if (!m_OBJSourceLocation.empty() && !m_Location.empty())
				{

					m_Vertices.clear();
					m_Indices.clear();

					DEBUG_INFO("Loading Mesh-File '{}'...", m_OBJSourceLocation);

					tinyobj::attrib_t attributes;

					std::vector<tinyobj::shape_t> shapes;
					std::vector<tinyobj::material_t> materials;

					std::string warning;
					std::string error;

					if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, m_OBJSourceLocation.c_str()))
					{
						DEBUG_ERROR("Failed to load OBJ file '{}'!", m_OBJSourceLocation);
					}

					if (!warning.empty())
					{
						DEBUG_WARN("[TINYOBJLOADER] {}", warning);
					}

					if (!error.empty())
					{
						DEBUG_ERROR("[TINYOBJLOADER] {}", error);
					}

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
								uniqueVertices[position] = static_cast<uint32_t>(m_Vertices.size());
								Makeshift::Vertex vtx;
								vtx.position = position;
								m_Vertices.push_back(vtx);
							}

							m_Indices.push_back(uniqueVertices[position]);
						}
					}

					Json::Value root;

					DEBUG_INFO("Writing Mesh-File '{}'...", m_Location);

					Json::Value vertices;
					for each (auto vertex in m_Vertices)
					{
						Json::Value vertexNode;
						vertexNode["Position"]["x"] = vertex.position.x;
						vertexNode["Position"]["y"] = vertex.position.y;
						vertexNode["Position"]["z"] = vertex.position.z;
						vertices.append(vertexNode);
					}

					Json::Value indices;
					for each (auto index in m_Indices)
					{
						Json::Value indexNode = index;
						indices.append(indexNode);
					}

					root["Vertices"] = vertices;
					root["Indices"] = indices;

					Json::StyledWriter writer;

					std::ofstream file(m_Location);
					if (file.is_open())
					{
						file << writer.write(root);
						file.close();
					}
					else
					{
						DEBUG_ERROR("Failed to write Mesh-File to location '{}'", m_Location);
					}
				}
			}

			ImGui::End();

		}

	}

}