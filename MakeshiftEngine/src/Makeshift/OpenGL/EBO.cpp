// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "EBO.h"

#include "Makeshift/Debug/Log.h"

#include <glad/glad.h>

namespace Makeshift
{

	EBO::EBO(const unsigned int* indices, unsigned int indexCount)
	{
		DEBUG_TRACE("Makeshift::EBO::EBO()");

		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

		m_IndexCount = indexCount;

		
	}

	EBO::~EBO()
	{
		DEBUG_TRACE("Makeshift::EBO::~EBO()");

		glDeleteBuffers(1, &m_ID);
	}

	void EBO::bind() const
	{
		DEBUG_TRACE("Makeshift::EBO::bind()");

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

		
	}

	void EBO::unbind() const
	{
		DEBUG_TRACE("Makeshift::EBO::unbind()");

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		
	}

	unsigned int EBO::getIndexCount() const
	{
		//DEBUG_TRACE("Makeshift::EBO::getIndexCount()");

		return m_IndexCount;

		
	}

}