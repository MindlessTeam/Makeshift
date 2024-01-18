// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Shader.h"
#include "MaterialProperty.h"

#include <vector>
#include <memory>

namespace Makeshift
{

	// Material - Resource
	// --------------------------------------
	// A Resource representing a Material
	struct Material : public Resource
	{

	public:
		struct Data
		{
			std::shared_ptr<Shader> shader;
			std::vector<std::shared_ptr<MaterialProperty>> materialProperties;
		};

	public:
		~Material() = default;

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