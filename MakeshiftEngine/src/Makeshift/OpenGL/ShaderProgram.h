// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace Makeshift
{

	class ShaderProgram
	{

	public:
		ShaderProgram() {};
		ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
		//TODO: ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource)
		//TODO: ShaderProgram(const std::string& computeSource) - perhaps a separate class?

		void use();

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;

	private:
		unsigned int m_ID;

	};

}