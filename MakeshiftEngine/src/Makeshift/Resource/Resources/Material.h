// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

#include "Shader.h"

#include <vector>
#include <memory>

namespace Json // Forward-Decl
{
	class Value;
}

namespace Makeshift
{

	//TODO: Rethink the Material-Properties system, don't work they way its supposed to...

	struct MaterialProperty
	{
		std::string uniformName;
		int location;
		virtual void apply(std::shared_ptr<ShaderProgram> program) = 0;

	public:
		virtual void serialize(Json::Value& JsonValue) = 0;
		virtual void deSerialize(const Json::Value& JsonValue) = 0;

	public:
		static std::shared_ptr<MaterialProperty> create(std::string propertyType);

	};

	struct MaterialPropertyFloat : public MaterialProperty
	{
		float value;
		virtual void apply(std::shared_ptr<ShaderProgram> program) override
		{
			program->setFloat(location, value);
		}

	public:
		virtual void serialize(Json::Value& JsonValue) override;
		virtual void deSerialize(const Json::Value& JsonValue) override;
	};

	struct MaterialPropertyInt : public MaterialProperty
	{
		int value;
		virtual void apply(std::shared_ptr<ShaderProgram> program) override
		{
			program->setInt(location, value);
		}

	public:
		virtual void serialize(Json::Value& JsonValue) override;
		virtual void deSerialize(const Json::Value& JsonValue) override;
	};

	struct MaterialPropertyBool : public MaterialProperty
	{
		bool value;
		virtual void apply(std::shared_ptr<ShaderProgram> program) override
		{
			program->setBool(location, value);
		}

	public:
		virtual void serialize(Json::Value& JsonValue) override;
		virtual void deSerialize(const Json::Value& JsonValue) override;
	};

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