// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Mesh.h"

#include "Makeshift/Debug/Log.h"

#include "Makeshift/Makeshift.hpp"

#include <fstream>
#include <json/json.h>

namespace Makeshift
{

	void Mesh::load(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Mesh::load()");

		DEBUG_INFO("Loading Mesh '{}'", location);

		std::ifstream file(location);

		if (!file.is_open())
		{
			DEBUG_ERROR("Failed to open JSON file '{}'", location);
			return;
		}

		Json::CharReaderBuilder reader;
		std::string errors;

		Json::Value root;

		if (!Json::parseFromStream(reader, file, &root, &errors))
		{
			file.close();
			DEBUG_ERROR("Failed to parse JSON from file '{}' with errors '{}'", location, errors);
			return;
		}

		file.close();

		const Json::Value& vertices = root["Vertices"];
		for (const Json::Value vertexNode : vertices)
		{
			Vertex vertex;
			vertex.position.x = vertexNode["Position"]["x"].asFloat();
			vertex.position.y = vertexNode["Position"]["y"].asFloat();
			vertex.position.z = vertexNode["Position"]["z"].asFloat();

			vertex.UV.x = vertexNode["UV"]["x"].asFloat();
			vertex.UV.y = vertexNode["UV"]["y"].asFloat();
			
			m_Data.vertices.push_back(vertex);
		}

		const Json::Value& indices = root["Indices"];
		for (const Json::Value& indexNode : indices)
		{
			m_Data.indices.push_back(indexNode.asUInt());
		}

		std::shared_ptr<VertexBufferLayout> layout = std::make_shared<VertexBufferLayout>();
		layout->Push(GL_FLOAT, 3, false);
		layout->Push(GL_FLOAT, 2, false);
		
		m_Data.vao = std::make_shared<VAO>();

		m_Data.vao->bind();

		std::shared_ptr<VBO> vbo = std::make_shared<VBO>(m_Data.vertices.data(), sizeof(Vertex) * m_Data.vertices.size());
		std::shared_ptr<EBO> ebo = std::make_shared<EBO>(m_Data.indices.data(), sizeof(unsigned int) * m_Data.indices.size());

		m_Data.vao->addVBO(vbo, layout);
		m_Data.vao->addEBO(ebo);

		m_Data.vertices.data()->position.x;

		m_Data.vao->unbind();

	}

	void Mesh::save(const std::string& location)
	{
		DEBUG_TRACE("Makeshift::Mesh::save()");

		Json::Value root;

		Json::Value vertices;
		for (auto vertex : m_Data.vertices)
		{
			Json::Value vertexNode;

			vertexNode["Position"]["x"] = vertex.position.x;
			vertexNode["Position"]["y"] = vertex.position.y;
			vertexNode["Position"]["z"] = vertex.position.z;

			vertexNode["UV"]["x"] = vertex.UV.x;
			vertexNode["UV"]["y"] = vertex.UV.y;

			vertices.append(vertexNode);

		}
		root["Vertices"] = vertices;

		Json::Value indices;
		for (auto index : m_Data.indices)
		{
			indices.append(index);
		}
		root["Indices"] = indices;

		DEBUG_INFO("Writing Mesh-File '{}'...", location);

		Json::StyledWriter writer;

		std::ofstream file(location);
		if (file.is_open())
		{
			file << writer.write(root);
			file.close();
		}
		else
		{
			DEBUG_ERROR("Failed to write Mesh-File to location '{}'", location);
		}

	}

	void Mesh::renderIMGUI()
	{

		ImGui::Text("VertexCount: %d", m_Data.vertices.size());

		if (ImGui::BeginTable(std::string(m_Location + "Table").c_str(), 3))
		{

			ImGui::TableSetupColumn("X");
			ImGui::TableSetupColumn("Y");
			ImGui::TableSetupColumn("Z");
			ImGui::TableHeadersRow();

			for (auto vertex : m_Data.vertices)
			{
				ImGui::TableNextRow();
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("%f", vertex.position.x);

				ImGui::TableSetColumnIndex(1);
				ImGui::Text("%f", vertex.position.y);

				ImGui::TableSetColumnIndex(2);
				ImGui::Text("%f", vertex.position.z);
			}
		
			ImGui::EndTable();
		}

		ImGui::Text("IndexCount: %d", m_Data.indices.size());

		for (auto index : m_Data.indices)
		{
			ImGui::Text("%d", index);
		}
	}

}