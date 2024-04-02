// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace Makeshift::OpenGL
{

	// Shader Program
	// ---------------------------------------------
	// A wrapper for an OpenGL Shader Program.
	class ShaderProgram
	{

	public:
		ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
		//TODO: ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource, const std::string& geometrySource)
		//TODO: ShaderProgram(const std::string& computeSource) - perhaps a separate class?
		~ShaderProgram();

		// ShaderProgram::use()
		// -----------------------------------------
		// Prepares the ShaderProgram for usage.
		void use();

		void setBool(int location, bool value) const;
		void setInt(int location, int value) const;
		void setFloat(int location, float value) const;

	public:
		// ShaderProgram::getRenderID()
		// -----------------------------------------
		// Returns:
		// - The ID the ShaderProgram is assigned to
		unsigned int getRenderID() const { return m_ID; }

	private:
		unsigned int m_ID = 0;

	};

}