// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <map>
#include <memory>
#include <functional>
#include <string>

#include "Makeshift/OpenGL/ShaderProgram.h"

#include "Makeshift/Debug/Log.h"

namespace Json //Forward-Decl
{
	struct Value;
}

namespace Makeshift
{

	// Material Property
	// ---------------------------------------------
	// Defines a property of a material.
	// (e.g. a float or a texture)
	struct MaterialProperty
	{

	public:
		std::string uniformName;
		int location;

		bool wasModified;

	public:
		// MaterialProperty::apply()
		// -----------------------------------------
		// applies the material property to the
		// shader.
		//
		// Parameters:
		// - program: The Shader Program to apply to.
		virtual void apply(std::shared_ptr<OpenGL::ShaderProgram> program) = 0;

		// MaterialProperty::serialize()
		// -----------------------------------------
		// Parses the properties data to Json.
		//
		// Parameters:
		// - jsonValue: the value to parse to
		virtual void serialize(Json::Value& jsonValue) = 0;

		// MaterialProperty::deSerialize()
		// -----------------------------------------
		// Reads the properties data from Json.
		//
		// Parameters:
		// - jsonValue: the value to read from
		virtual void deSerialize(const Json::Value& jsonValue) = 0;

	public:
		virtual void renderEditor() {}

	public:
		// MaterialProperty::getType()
		// -----------------------------------------
		// Returns:
		// - The type of Material Property (e.g. bool)
		virtual std::string getType() = 0;

	};

	// Material Property Registry
	// ---------------------------------------------
	// A registry to keep track of all material
	// properties. Used during the loading process.
	class MaterialPropertyRegistry
	{

	public:
		// MaterialPropertyRegistry::registerMaterialProperty()
		// -----------------------------------------
		// Registers a Material Property.
		//
		// Parameters:
		// - <T>: the type of property to register
		template<typename T>
		static void registerMaterialProperty();

	public:
		// MaterialPropertyRegistry::createMaterialProperty()
		// -----------------------------------------
		// Creates a material property based on the
		// given type.
		//
		// Parameters:
		// - name: the type of material property
		//
		// Returns:
		// - a shared_ptr to the created material property
		static std::shared_ptr<MaterialProperty> createMaterialProperty(const std::string& name);

	private:
		static std::map<std::string, std::function<std::shared_ptr<MaterialProperty>()>> s_MaterialPropertyRegistry;

	};

	template<typename T>
	inline void MaterialPropertyRegistry::registerMaterialProperty()
	{
		DEBUG_TRACE("Makeshift::MaterialPropertyRegistry::registerMaterialProperty()");
		T materialProperty;

		DEBUG_INFO("Registering Material-Property '{}'", materialProperty.getName());

		s_MaterialPropertyRegistry[materialProperty.getName()] = []() {return std::make_shared<T>(); };

	}

}