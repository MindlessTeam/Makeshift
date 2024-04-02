// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <vector>

#include "Makeshift/Utility/OpenGLTypes.h"

namespace Makeshift::OpenGL
{

	// Vertex Buffer Element
	// ---------------------------------------------
	// An Internal Representation of a Vertex Buffer
	// Element used in the layout.
	struct VertexBufferElement
	{
		unsigned int type, count;
		bool normalized;

		// VertexBufferElement::getSizeOfType()
		// -----------------------------------------
		// Parameters:
		// - type: The type to be queried for size
		//NOTE: Currently not all types are implemented. See definition
		// 
		// Returns:
		// - the size of the given type (or 0 if unknown)
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

	// Vertex Buffer Layout
	// ---------------------------------------------
	// The layout of a vertex buffer. Describes
	// which Data goes where.
	struct VertexBufferLayout
	{

	public:
		// VertexBufferLayout::push()
		// -----------------------------------------
		// Pushes a new Element to the Layout.
		// 
		// Parameters:
		// - type: the type of the element
		// - count: the amount
		// - normalized: whether or not the element is normalized
		inline void push(unsigned int type, unsigned int count, bool normalized)
		{
			m_VertexBufferElements.push_back({ type, count, normalized });
			m_Stride += VertexBufferElement::getSizeOfType(type) * count;
		}

		// VertexBufferLayout::getVertexBufferElements()
		// -----------------------------------------
		// Returns:
		// - the elements in the VertexBufferLayout
		inline const std::vector<VertexBufferElement>& getVertexBufferElements() const
		{
			return m_VertexBufferElements;
		}

		// VertexBufferLayout::getStride()
		// -----------------------------------------
		// Returns:
		// - The Stride of the Layout
		inline unsigned int getStride() const
		{
			return m_Stride;
		}

	private:
		std::vector<VertexBufferElement> m_VertexBufferElements;
		unsigned int m_Stride = 0;

	};

	// Vertex Buffer Object
	// ---------------------------------------------
	// A wrapper for an OpenGL VBO.
	class VBO
	{

	public:
		VBO(const void* data, unsigned int size);
		~VBO();

		// VBO::bind()
		// -----------------------------------------
		// Binds the VBO.
		void bind() const;

		// VBO::unbind()
		// -----------------------------------------
		// Unbinds the VBO.
		void unbind() const;

	public:
		// VBO::getRenderID()
		// -----------------------------------------
		// Returns:
		// - The ID the VBO has been assigned
		unsigned int getRenderID() const { return m_ID; }

	private:
		unsigned int m_ID;

	};

}