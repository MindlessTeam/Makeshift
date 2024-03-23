// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "ShaderTest.h"

#include <Makeshift/Makeshift.hpp>

#include <glad/glad.h>

namespace Makeshift
{

	void ShaderTest::serialize(Json::Value& value)
	{

		//value["Mesh"] = m_Mesh->m_Location;
		//value["Material"] = m_Material->m_Location;

	}

	void ShaderTest::deSerialize(Json::Value value)
	{

		//m_Mesh = Engine::getInstance().getResourceMap()->addResource<Mesh>(value["Mesh"].asString());
		//m_Material = Engine::getInstance().getResourceMap()->addResource<Material>(value["Material"].asString());

	}

	void ShaderTest::onInit()
	{

	}

    void ShaderTest::onUpdate()
    {

        //m_Material->getData().shader->getData().shaderProgram->use();
		//
		//m_Mesh->getData().vao->bind();
		//
        //glDrawElements(GL_TRIANGLES, m_Mesh->getData().indices.size(), GL_UNSIGNED_INT, 0);
		//
        //m_Mesh->getData().vao->unbind();

    }

	void ShaderTest::onEnable()
	{

	}

	void ShaderTest::onDisable()
	{

	}

}
