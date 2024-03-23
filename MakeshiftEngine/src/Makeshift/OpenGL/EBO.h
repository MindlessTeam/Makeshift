// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift::OpenGL
{

	class EBO // or IBO, i guess?
	{

	public:
		EBO(const unsigned int* indices, unsigned int indexCount);
		//TODO: EBO(const unsigned short* indices, unsigned int indexCount);
		~EBO();

		void bind() const;
		void unbind() const;

	public:
		unsigned int getRenderID() const { return m_ID; }
		unsigned int getIndexCount() const { return m_IndexCount; }

	private:
		unsigned int m_ID;
		unsigned int m_IndexCount;

	};

}