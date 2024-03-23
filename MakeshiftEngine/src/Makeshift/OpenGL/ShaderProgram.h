// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace Makeshift::OpenGL
{

	class ShaderProgram
	{

	public:
		ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
		//TODO: ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource)
		//TODO: ShaderProgram(const std::string& computeSource) - perhaps a separate class?
		~ShaderProgram();

		void use();

		void setBool(int location, bool value) const;
		void setInt(int location, int value) const;
		void setFloat(int location, float value) const;

	public:
		unsigned int getRenderID() const { return m_ID; }

	private:
		unsigned int m_ID = 0;

	};

}