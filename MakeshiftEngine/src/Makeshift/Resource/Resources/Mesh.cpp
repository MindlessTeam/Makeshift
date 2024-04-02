// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Mesh.h"

#include "Makeshift/Debug/Log.h"

#include "Makeshift/Makeshift.hpp"
#include "Makeshift/Version.h"

#include <fstream>
#include <json/json.h>

namespace Makeshift
{

	void Mesh::loadJson(Json::Value root)
	{
		DEBUG_TRACE("Makeshift::Mesh::loadJson()");

		std::vector<Vertex> vertexData;
		std::vector<uint32_t> indexData;

		const Json::Value& vertices = root["Vertices"];
		for (const Json::Value vertexNode : vertices)
		{
			Vertex vertex;
			vertex.position.x = vertexNode["Position"]["x"].asFloat();
			vertex.position.y = vertexNode["Position"]["y"].asFloat();
			vertex.position.z = vertexNode["Position"]["z"].asFloat();

			vertex.UV.x = vertexNode["UV"]["x"].asFloat();
			vertex.UV.y = vertexNode["UV"]["y"].asFloat();
			
			vertexData.push_back(vertex);
		}

		const Json::Value& indices = root["Indices"];
		for (const Json::Value& indexNode : indices)
		{
			indexData.push_back(indexNode.asUInt());
		}
		m_Data.indexCount = indexData.size();

		std::shared_ptr<OpenGL::VertexBufferLayout> layout = std::make_shared<OpenGL::VertexBufferLayout>();
		layout->push(GL_FLOAT, 3, false);
		layout->push(GL_FLOAT, 2, false);
		
		m_Data.vao = std::make_shared<OpenGL::VAO>();

		m_Data.vao->bind();

		std::shared_ptr<OpenGL::VBO> vbo = std::make_shared<OpenGL::VBO>(vertexData.data(), sizeof(Vertex) * vertexData.size());
		std::shared_ptr<OpenGL::EBO> ebo = std::make_shared<OpenGL::EBO>(indexData.data(), sizeof(unsigned int) * indexData.size());

		m_Data.vao->addVBO(vbo, layout);
		m_Data.vao->addEBO(ebo);

		m_Data.vao->unbind();

	}

}