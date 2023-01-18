// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
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

		int success;
		char infoLog[512];

		unsigned int vertex, fragment;

		DEBUG_INFO("Compiling vertex shader...");
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			DEBUG_ERROR("Failed to compile vertex shader! - {}", infoLog);
		}

		DEBUG_INFO("Compiling fragment shader...");
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			DEBUG_ERROR("Failed to compile fragment shader! - {}", infoLog);
		}

		DEBUG_INFO("Linking shader program...");
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertex);
		glAttachShader(m_ID, fragment);
		glLinkProgram(m_ID);

		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
			DEBUG_ERROR("Failed to link shader program! - {}", infoLog);
		}

		// We don't need them anymore, so... THROW 'EM IN THE TRASH!
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void Shader::bind()
	{

		

	}

}