// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace Makeshift
{

	// Shader
	// -----------------------------------------
	// Wrapper for an OpenGL Shader.
	// (Technically a wrapper for a shader program,
	// but who cares...)
	struct Shader
	{

		//TODO: In the future, create constructors with Geometry Shaders, Tesselation, etc.
		Shader(const std::string& vertexShader, const std::string& fragmentShader);

		void bind();
		void unbind();

		//TODO: Helper functions for setting uniforms

	private:
		unsigned int m_ID;

	};

}