// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift::OpenGL
{

	// Element Buffer Object
	// ---------------------------------------------
	// A wrapper for an OpenGL EBO.
	class EBO
	{

	public:
		EBO(const unsigned int* indices, unsigned int indexCount);
		//TODO: EBO(const unsigned short* indices, unsigned int indexCount);
		~EBO();

		// EBO::bind()
		// -----------------------------------------
		// Binds the EBO for use.
		void bind() const;

		// EBO::unbind()
		// -----------------------------------------
		// Unbinds the EBO. This is not necessary
		// during rendering as the next EBO will
		// override the binding anyway.
		void unbind() const;

	public:
		// EBO::getRenderID()
		// -----------------------------------------
		// Returns:
		// - the ID the EBO is assigned to
		unsigned int getRenderID() const { return m_ID; }

		// EBO::getIndexCount()
		// -----------------------------------------
		// Returns:
		// - the amount of indices in the buffer
		unsigned int getIndexCount() const { return m_IndexCount; }

	private:
		unsigned int m_ID;
		unsigned int m_IndexCount;

	};

}