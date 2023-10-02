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
			Vertex vtx;
			vtx.position.x = vertexNode["Position"]["x"].asFloat();
			vtx.position.y = vertexNode["Position"]["y"].asFloat();
			vtx.position.z = vertexNode["Position"]["z"].asFloat();
			
			m_Data.vertices.push_back(vtx);
		}

		const Json::Value& indices = root["Indices"];
		for (const Json::Value& indexNode : indices)
		{
			m_Data.indices.push_back(indexNode.asUInt());
		}

		std::shared_ptr<VertexBufferLayout> layout;
		layout->Push(GL_FLOAT, 3, false);

		std::shared_ptr<VBO> vbo = std::make_shared<VBO>(m_Data.vertices.data(), m_Data.vertices.size());
		std::shared_ptr<EBO> ebo = std::make_shared<EBO>(m_Data.indices.data(), m_Data.indices.size());

		m_Data.vao.addVBO(vbo, layout);
		m_Data.vao.addEBO(ebo);

	}

}