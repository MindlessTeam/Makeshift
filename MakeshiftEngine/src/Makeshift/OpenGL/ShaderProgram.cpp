// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "ShaderProgram.h"

#include "Makeshift/Debug/Log.h"

#include <glad/glad.h>

namespace Makeshift
{

	ShaderProgram::ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
	{
		DEBUG_TRACE("Makeshift::ShaderProgram::ShaderProgram()");

		unsigned int vertexShader, fragmentShader;
		const char* vSource = vertexSource.c_str();
		const char* fSource = fragmentSource.c_str();
		int success;
		char info[512];

		DEBUG_INFO("Compiling Vertex Shader...");

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vSource, NULL);

		glCompileShader(vertexShader);

		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, info);
			DEBUG_FATAL("Vertex shader compilation failed with Info: '{}'", info);
		}

		DEBUG_INFO("Compiling Fragment Shader...");

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fSource, NULL);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, info);
			DEBUG_FATAL("Fragment shader compilation failed with Info: '{}'", info);
		}

		DEBUG_INFO("Creating Shader Program...");

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShader);
		glAttachShader(m_ID, fragmentShader);

		glLinkProgram(m_ID);

		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(m_ID, 512, NULL, info);
			DEBUG_FATAL("Shader Program creation failed with Info: '{}'", info);
		}

		// cleanup
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}

	void ShaderProgram::use()
	{
		glUseProgram(m_ID);
	}

	void ShaderProgram::setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), (int)value);
	}

	void ShaderProgram::setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void ShaderProgram::setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
	}

}