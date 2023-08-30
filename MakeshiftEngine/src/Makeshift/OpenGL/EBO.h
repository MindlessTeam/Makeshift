// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

namespace Makeshift
{

	class EBO // or IBO, i guess?
	{

	public:
		EBO(const unsigned int* indices, unsigned int indexCount);
		//TODO: EBO(const unsigned short* indices, unsigned int indexCount);
		~EBO();

		void bind() const;
		void unbind() const;

		unsigned int getIndexCount() const;

	private:
		unsigned int m_ID;
		unsigned int m_IndexCount;

	};

}