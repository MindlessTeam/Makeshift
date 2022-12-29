// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "VertexBuffer.h"
#include "Makeshift/Debug/Log.h"

#include <glad/glad.h>

namespace Makeshift
{

	VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		DEBUG_TRACE("Makeshift::VertexBuffer::VertexBuffer()");

		DEBUG_INFO("Creating VertexBuffer...");
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

	}

	VertexBuffer::VertexBuffer(const void* data, unsigned int size, bool dynamic)
	{
		DEBUG_TRACE("Makeshift::VertexBuffer::VertexBuffer()");

		DEBUG_INFO("Creating VertexBuffer...");
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		
		switch (dynamic) // Could be an if, I guess...
		{
		case false:
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			break;
		case true:
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
			break;
		}

	}

	void VertexBuffer::bind()
	{

		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	
	}

	void VertexBuffer::unbind()
	{
	
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	
	}

}