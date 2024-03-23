//// ----------------------------------------------
//// Copyright (c) 2022-2024 Aaron Kerker
//// MIT-Licensed: https://opensource.org/licenses/MIT
//// ----------------------------------------------
//
//#pragma once
//
//#include <map>
//#include <functional>
//#include <string>
//
//namespace Json //Forward-Decl
//{
//	struct Value;
//}
//
//namespace Makeshift
//{
//
//	struct MaterialProperty
//	{
//
//	public:
//		std::string uniformName;
//		int location;
//
//	public:
//		virtual void apply(std::shared_ptr<OpenGL::ShaderProgram> program) = 0;
//		virtual void serialize(Json::Value& jsonValue) = 0;
//		virtual void deSerialize(const Json::Value& jsonValue) = 0;
//
//	public:
//		virtual void getName() = 0;
//
//	};
//
//	class MaterialPropertyRegistry
//	{
//
//	public:
//		template<typename T>
//		static void registerMaterialProperty();
//
//	public:
//		static std::shared_ptr<MaterialProperty> createMaterialProperty(std::string name);
//
//	private:
//		static std::map<std::string, std::function<std::shared_ptr<MaterialProperty>>> s_MaterialPropertyRegistry;
//
//	};
//
//	template<typename T>
//	inline void MaterialPropertyRegistry::registerMaterialProperty()
//	{
//		DEBUG_TRACE("Makeshift::MaterialPropertyRegistry::registerMaterialProperty()");
//		T materialProperty;
//
//		DEBUG_INFO("Registering Material-Property '{}'", materialProperty.getName());
//
//		s_MaterialPropertyRegistry[materialProperty.getName()] = []() {return std::make_shared<T>(); };
//
//	}
//
//}