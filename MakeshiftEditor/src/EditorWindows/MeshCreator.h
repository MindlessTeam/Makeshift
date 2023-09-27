// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <string>

#include <Makeshift/Resource/Mesh.h>

namespace MakeshiftEditor
{

	struct MeshCreator
	{

		bool enabled = false;

		void renderIMGUI();

	private:
		std::string m_OBJSourceLocation;
		std::string m_Location;

		std::vector<Makeshift::Vertex> m_Vertices;
		std::vector<uint32_t> m_Indices;

	};

}