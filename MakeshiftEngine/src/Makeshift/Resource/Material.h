// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Shader.h"

#include <vector>
#include <memory>

namespace Makeshift
{


	//struct MaterialProperty
	//{
	//	std::string uniformName;
	//};

	// Material - Resource
	// --------------------------------------
	// <description>
	struct Material : public Resource
	{

	public:
		struct Data
		{
			std::shared_ptr<Shader> shader;
			//std::vector<MaterialProperty> materialProperties;
		};

	public:
		~Material() = default;

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