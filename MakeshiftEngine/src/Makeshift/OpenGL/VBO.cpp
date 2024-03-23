// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "VBO.h"

#include "Makeshift/Debug/Log.h"

#include <glad/glad.h>

namespace Makeshift::OpenGL
{

	VBO::VBO(const void* data, unsigned int size)
	{
		DEBUG_TRACE("Makeshift::VBO::VBO()");

		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		
	}

	VBO::~VBO()
	{
		DEBUG_TRACE("Makeshift::VBO::~VBO()");

		glDeleteBuffers(1, &m_ID);

		
	}

	void VBO::bind() const
	{
		DEBUG_TRACE("Makeshift::VBO::bind()");

		glBindBuffer(GL_ARRAY_BUFFER, m_ID);

		
	}

	void VBO::unbind() const
	{
		DEBUG_TRACE("Makeshift::VBO::unbind()");

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		
	}

}