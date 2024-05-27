// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Makeshift/OpenGL/ShaderProgram.h"

#include <memory>

namespace Makeshift
{

	// Shader - Resource
	// --------------------------------------
	// A Resource representing a 
	// Shader-Program.
	struct Shader : public Resource
	{

	public:
		std::string getType() override
		{
			return "Shader";
		}

	public:
		struct Data
		{
			std::shared_ptr<OpenGL::ShaderProgram> shaderProgram;
		};

	public:
		~Shader() = default;

		Data& getData() { return m_Data; }
		void setData(Data data) { m_Data = data; }

	public:
		// Inherited via Resource
		virtual void loadJson(Json::Value value) override;

	public:
		static void saveShader(const std::string& location, const std::string& vertexCode, const std::string& fragmentCode);

	private:
		Data m_Data;

	};

}