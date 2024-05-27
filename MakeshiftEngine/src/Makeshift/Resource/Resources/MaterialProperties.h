// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "MaterialProperty.h"

namespace Makeshift
{

	struct FloatProperty : public MaterialProperty
	{

	public: // Inherited from MaterialProperty
		virtual void apply(std::shared_ptr<OpenGL::ShaderProgram> program) override;
		virtual void serialize(Json::Value& jsonValue) override;
		virtual void deSerialize(const Json::Value& jsonValue) override;

		virtual void renderEditor() override;

	public:
		virtual std::string getType()
		{
			return "FloatProperty";
		}

	private:
		float m_Value;

	};

	struct IntProperty : public MaterialProperty
	{

	public: // Inherited from MaterialProperty
		virtual void apply(std::shared_ptr<OpenGL::ShaderProgram> program) override;
		virtual void serialize(Json::Value& jsonValue) override;
		virtual void deSerialize(const Json::Value& jsonValue) override;

		virtual void renderEditor() override;

	public:
		virtual std::string getType()
		{
			return "FloatProperty";
		}

	private:
		int m_Value;

	};

	struct BoolProperty : public MaterialProperty
	{

	public: // Inherited from MaterialProperty
		virtual void apply(std::shared_ptr<OpenGL::ShaderProgram> program) override;
		virtual void serialize(Json::Value& jsonValue) override;
		virtual void deSerialize(const Json::Value& jsonValue) override;

		virtual void renderEditor() override;

	public:
		virtual std::string getType()
		{
			return "FloatProperty";
		}

	private:
		bool m_Value;

	};

}