// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

namespace MakeshiftEditor
{

	struct MaterialCreator
	{

		bool enabled = false;

		void renderIMGUI();

	private:
		std::string m_VertexText;
		std::string m_FragmentText;
		std::string m_ShaderLocation;

		std::string m_Location;

		bool m_CreateNewShader;

	};

}