// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <Makeshift/Resource/Resource.h>

namespace Makeshift
{

	// $itemname$ - Resource
	// --------------------------------------
	// <description>
	struct $itemname$ : public Resource
	{

	public:
		struct Data
		{
			
		};

	public:
		~$itemname$() = default;

		Data& getData() { return m_Data; }
#ifdef EDITOR
		void setData(Data data) { m_Data = data; }
#endif

	public:
		// Inherited via Resource
		virtual void load(const std::string& location) override;

#ifdef EDITOR
		virtual void renderIMGUI() override
		{

		}
#endif

	private:
		Data m_Data;

	};

}