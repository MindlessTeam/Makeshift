// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Level/Entity.h>

#include <Makeshift/Resource/Resources/Material.h>
#include <Makeshift/Resource/Resources/Mesh.h>

namespace Makeshift
{

	// ShaderTest - Entity
	// --------------------------------------
	// <description>
	class ShaderTest : public Entity
	{

	public:
		std::string getName() override
		{
			return "ShaderTest";
		}

	public:
		void serialize(Json::Value& value) override;
		void deSerialize(Json::Value value) override;

	protected:
		// Initialize all your resources here
		void onInit() override;
		// This function is called every frame.
		void onUpdate() override;

		void onEnable() override;
		void onDisable() override;

	private: // Resources
		std::shared_ptr<Mesh> m_Mesh;
		std::shared_ptr<Material> m_Material;

	};

}