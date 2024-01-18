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
	// Shader-Program
	struct Shader : public Resource
	{

	public:
		struct Data
		{
			std::string vertexShaderSource, fragmentShaderSource; //TODO: Geometry/Compute
			std::shared_ptr<ShaderProgram> shaderProgram;
		};

	public:
		~Shader() = default;

		Data& getData() { return m_Data; }
		void setData(Data data) { m_Data = data; }

	public:
		// Inherited via Resource
		virtual void load(const std::string& location) override;
		virtual void save(const std::string& location) override;

		virtual void renderIMGUI() override;

	private:
		Data m_Data;

	};

}