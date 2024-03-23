// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
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
		std::string getType() override
		{
			return "$itemname";
		}

	public:
		struct Data
		{
			
		};

	public:
		~$itemname$() = default;

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