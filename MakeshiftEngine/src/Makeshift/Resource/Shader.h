// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Makeshift/OpenGL/ShaderProgram.h"

namespace Makeshift
{

	// Shader - Resource
	// --------------------------------------
	// <description>
	struct Shader : public Resource
	{

	public:
		struct Data
		{
			std::string vertexShaderSource, fragmentShaderSource; //TODO: Geometry/Compute
			ShaderProgram shaderProgram;
		};

	public:
		~Shader() = default;

		Data& getData() { return m_Data; }
#ifdef EDITOR
		void setData(Data data) { m_Data = data; }
#endif

	public:
		// Inherited via Resource
		virtual void load(const std::string& location) override;

#ifdef EDITOR
		virtual void renderIMGUI() override
		{

		}
#endif

	private:
		Data m_Data;

	};

}