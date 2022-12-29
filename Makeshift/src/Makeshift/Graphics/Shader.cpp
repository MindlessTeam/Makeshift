// ----------------------------------------------
// Copyright (c) 2022 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "Shader.h"
#include "Makeshift/Debug/Log.h"

#include <glad/glad.h>

namespace Makeshift
{

	Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		DEBUG_TRACE("Makeshift::Shader::Shader()");
		
		const char* vertexCode = vertexShader.c_str();
		const char* fragmentCode = fragmentShader.c_str();

		unsigned int vertex, fragment;

		

	}

}