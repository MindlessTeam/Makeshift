// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "MaterialProperties.h"

#include <glad/glad.h>

#include <json/json.h>

#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>

namespace Makeshift
{

	void FloatProperty::apply(std::shared_ptr<OpenGL::ShaderProgram> program)
	{

		if (location == 0)
		{
			location = glGetUniformLocation(program->getRenderID(), uniformName.c_str());
		}
		if (uniformName != "" && wasModified && location != 0)
		{
			program->setFloat(location, m_Value);
		}

	}

	void FloatProperty::serialize(Json::Value& jsonValue)
	{

		jsonValue["Uniform"] = uniformName;
		jsonValue["Value"] = m_Value;
		
	}

	void FloatProperty::deSerialize(const Json::Value& jsonValue)
	{

		uniformName = jsonValue["Uniform"].asString();
		m_Value = jsonValue["Value"].asFloat();

	}

	void FloatProperty::renderEditor()
	{

		ImGui::InputTextWithHint("## UniformLocation", "Uniform Location", &uniformName);
		ImGui::SliderFloat("## FloatValue", &m_Value, 0, 1); // Usually, a float will be used to dicern a value between 0 and 1, e.g. blending a texture 0 being Texture A and 1 being Texture B

	}

	// -------------------------------------

	void IntProperty::apply(std::shared_ptr<OpenGL::ShaderProgram> program)
	{

		if (location == 0)
		{
			location = glGetUniformLocation(program->getRenderID(), uniformName.c_str());
		}
		if (uniformName != "" && wasModified && location != 0)
		{
			program->setInt(location, m_Value);
		}

	}

	void IntProperty::serialize(Json::Value& jsonValue)
	{

		jsonValue["Uniform"] = uniformName;
		jsonValue["Value"] = m_Value;

	}

	void IntProperty::deSerialize(const Json::Value& jsonValue)
	{

		uniformName = jsonValue["Uniform"].asString();
		m_Value = jsonValue["Value"].asInt();

	}

	void IntProperty::renderEditor()
	{

		ImGui::InputTextWithHint("## UniformLocation", "Uniform Location", &uniformName);
		ImGui::SliderInt("## IntValue", &m_Value, -10, 10);

	}

	// -------------------------------------

	void BoolProperty::apply(std::shared_ptr<OpenGL::ShaderProgram> program)
	{

		if (location == 0)
		{
			location = glGetUniformLocation(program->getRenderID(), uniformName.c_str());
		}
		if (uniformName != "" && wasModified && location != 0)
		{
			program->setBool(location, m_Value);
		}

	}

	void BoolProperty::serialize(Json::Value& jsonValue)
	{

		jsonValue["Uniform"] = uniformName;
		jsonValue["Value"] = m_Value;

	}

	void BoolProperty::deSerialize(const Json::Value& jsonValue)
	{

		uniformName = jsonValue["Uniform"].asString();
		m_Value = jsonValue["Value"].asBool();

	}

	void BoolProperty::renderEditor()
	{

		ImGui::InputTextWithHint("## UniformLocation", "Uniform Location", &uniformName);
		ImGui::Checkbox("## BoolValue", &m_Value);

	}

}
