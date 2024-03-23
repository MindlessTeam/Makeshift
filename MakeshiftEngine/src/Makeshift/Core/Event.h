// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <vector>
#include <functional>

namespace Makeshift
{

	template<typename... Args>
	class Event
	{

	public:
		void trigger(Args... args)
		{
			for (const auto& callback : m_Callbacks)
			{
				callback(args...);
			}
		}

		void subscribe(const std::function<void()>& callback)
		{
			m_Callbacks.push_back(callback);
		}

	private:
		std::vector<std::function<void(Args...)>> m_Callbacks;

	};
	
}