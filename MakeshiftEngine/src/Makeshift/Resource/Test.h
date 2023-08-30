// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Resource.h"

namespace Makeshift
{

	// Mesh - Resource
	// -----------------------------------------
	// Represents a 3d model
	struct TestRes : public Resource
	{

	public:
		struct Data
		{
			int wow;
		};
	public:
		~TestRes() = default;

		Data& getData() { return m_Data; }
#ifdef EDITOR
		void setData(Data data) { m_Data = data; }
#endif

	public:
		// Inherited via Resource
		virtual void load(const std::string& location) override
		{

		}

#ifdef EDITOR
		virtual void renderIMGUI() override
		{
			ImGui::Text(std::to_string(m_Data.wow));
		}
#endif

	private:
		Data m_Data;



	};

}