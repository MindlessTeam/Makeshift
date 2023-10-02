// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "VAO.h"

#include "Makeshift/Debug/Log.h"

#include <glad/glad.h>

namespace Makeshift
{

	VAO::VAO()
	{
		DEBUG_TRACE("Makeshift::VAO::VAO()");

		glGenVertexArrays(1, &m_ID);

		
	}

	VAO::~VAO()
	{
		DEBUG_TRACE("Makeshift::VAO::~VAO()");

		glDeleteVertexArrays(1, &m_ID);

		
	}

	void VAO::bind() const
	{
		//DEBUG_TRACE("Makeshift::VAO::bind()");

		glBindVertexArray(m_ID);

		
	}

	void VAO::unbind() const
	{
		//DEBUG_TRACE("Makeshift::VAO::unbind()");

		glBindVertexArray(0);

		
	}

	void VAO::addVBO(const std::shared_ptr<VBO>& vbo, const std::shared_ptr<VertexBufferLayout>& layout)
	{
		DEBUG_TRACE("Makeshift::VAO::addVBO()");

		bind();
		DEBUG_WARN("1");
		

		unsigned int offset = 0;

		for (const auto& element : layout->getVertexBufferElements())
		{

			glEnableVertexAttribArray(m_VBOIndex);

			DEBUG_WARN("2");
			
			glVertexAttribPointer(m_VBOIndex,
				element.count,
				element.type,
				element.normalized ? GL_TRUE : GL_FALSE,
				layout->getStride(),
				(const void*)offset);
			DEBUG_WARN("3");
			

			offset += element.count * VertexBufferElement::getSizeOfType(element.type);

			m_VBOIndex++;
		}

		m_VBOs.push_back({ vbo, layout });

	}

	void VAO::addEBO(const std::shared_ptr<EBO>& ebo)
	{
		DEBUG_TRACE("Makeshift::VAO::addEBO()");

		m_EBO = ebo;
	}

}