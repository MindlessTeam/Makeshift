// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <vector>

#include "Makeshift/Utility/OpenGLTypes.h"

namespace Makeshift::OpenGL
{

	struct VertexBufferElement
	{
		unsigned int type, count;
		bool normalized;

		static unsigned int getSizeOfType(unsigned int type) //TODO: Create internal type
		{
			switch (type)
			{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			default:
				return 0;
			}
		}
	};

	struct VertexBufferLayout
	{

	public:
		inline void Push(unsigned int type, unsigned int count, bool normalized)
		{
			m_VertexBufferElements.push_back({ type, count, normalized });
			m_Stride += VertexBufferElement::getSizeOfType(type) * count;
		}

		inline const std::vector<VertexBufferElement>& getVertexBufferElements() const
		{
			return m_VertexBufferElements;
		}

		inline unsigned int getStride() const
		{
			return m_Stride;
		}

	private:
		std::vector<VertexBufferElement> m_VertexBufferElements;
		unsigned int m_Stride = 0;

	};

	class VBO
	{

	public:
		VBO(const void* data, unsigned int size);
		~VBO();

		void bind() const;
		void unbind() const;

	public:
		unsigned int getRenderID() const { return m_ID; }

	private:
		unsigned int m_ID;

	};

}