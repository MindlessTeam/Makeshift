// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "VBO.h"
#include "EBO.h"

#include <vector>
#include <memory>

namespace Makeshift
{

	class VAO
	{

	public:
		VAO();
		~VAO();

		void bind() const;
		void unbind() const;

		void addVBO(const std::shared_ptr<VBO>& vbo, const std::shared_ptr<VertexBufferLayout>& layout);
		void addEBO(const std::shared_ptr<EBO>& ebo);

	public:
		unsigned int getRenderID() { return m_ID; }

	private:
		unsigned int m_ID;
		unsigned int m_VBOIndex = 0;
		std::vector<std::pair<std::shared_ptr<VBO>, std::shared_ptr<VertexBufferLayout>>> m_VBOs;
		std::shared_ptr<EBO> m_EBO;

	};

}