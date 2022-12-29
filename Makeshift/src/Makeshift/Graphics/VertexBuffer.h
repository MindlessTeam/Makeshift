// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{

	// Vertex Buffer
	// --------------------------------------------
	// Wrapper for an OpenGL VBO
	struct VertexBuffer
	{

		VertexBuffer(const void* data, unsigned int size);
		VertexBuffer(const void* data, unsigned int size, bool dynamic);

		void bind();
		void unbind();

		unsigned int getID() { return m_ID; }

	private:
		unsigned int m_ID;

	};

}