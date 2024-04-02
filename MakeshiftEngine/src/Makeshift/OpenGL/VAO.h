// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "VBO.h"
#include "EBO.h"

#include <vector>
#include <memory>

namespace Makeshift::OpenGL
{

	// Vertex Array Object
	// ---------------------------------------------
	// A wrapper for an OpenGL VAO.
	class VAO
	{

	public:
		VAO();
		~VAO();

		// VAO::bind()
		// -----------------------------------------
		// Binds the VAO for use.
		void bind() const;

		// VAO::unbind()
		// -----------------------------------------
		// Unbinds the VAO.
		void unbind() const;

		// VAO::addVBO()
		// -----------------------------------------
		// Adds a Vertex Buffer to the VAO.
		//
		// Parameters:
		// - vbo: the VBO to add
		// - layout: the data Layout of the VBO
		void addVBO(const std::shared_ptr<VBO>& vbo, const std::shared_ptr<VertexBufferLayout>& layout);
		void addEBO(const std::shared_ptr<EBO>& ebo);

	public:
		// VAO::getRenderID()
		// -----------------------------------------
		// Returns:
		// - the assigned ID of the VAO
		unsigned int getRenderID() const { return m_ID; }

		// VAO::getEBO()
		// -----------------------------------------
		// Returns:
		// - The EBO that is assigned to the VAO
		std::shared_ptr<EBO> getEBO() const { return m_EBO; }

	private:
		unsigned int m_ID;
		unsigned int m_VBOIndex = 0;
		std::vector<std::pair<std::shared_ptr<VBO>, std::shared_ptr<VertexBufferLayout>>> m_VBOs;
		std::shared_ptr<EBO> m_EBO;

	};

}