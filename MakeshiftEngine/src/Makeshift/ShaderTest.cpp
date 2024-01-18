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

		value["Mesh"] = m_Mesh->m_Location;
		value["Material"] = m_Material->m_Location;

	}

	void ShaderTest::deSerialize(Json::Value value)
	{

		m_Mesh = Engine::getInstance().getResourceMap()->addResource<Mesh>(value["Mesh"].asString());
		m_Material = Engine::getInstance().getResourceMap()->addResource<Material>(value["Material"].asString());

	}

	void ShaderTest::onInit()
	{

	}

    void ShaderTest::onUpdate()
    {
        std::cout << "Hi!" << std::endl;

        if (m_Material && m_Material->getData().shader)
        {
            m_Material->getData().shader->getData().shaderProgram->use();

            if (m_Mesh && m_Mesh->getData().vao->getRenderID() != 0)
            {
                std::cout << "VAO is valid. Drawing..." << std::endl;

                m_Mesh->getData().vao->bind();

                // Print additional information about VAO state before drawing
                std::cout << "Bound VAO ID: " << m_Mesh->getData().vao->getRenderID() << std::endl;

                
                glDrawElements(GL_TRIANGLES, m_Mesh->getData().indices.size(), GL_UNSIGNED_INT, 0);
                

                // Print additional information after drawing
                std::cout << "Drawing complete. Unbinding VAO." << std::endl;

                m_Mesh->getData().vao->unbind();
            }
            else
            {
                std::cerr << "Error: Invalid VAO." << std::endl;
            }
        }
        else
        {
            std::cerr << "Error: Invalid material or shader." << std::endl;
        }
    }

	void ShaderTest::onEnable()
	{

	}

	void ShaderTest::onDisable()
	{

	}

}
