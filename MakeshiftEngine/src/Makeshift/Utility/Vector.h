// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <glm/common.hpp>

namespace Makeshift
{

	namespace Util
	{

		struct Vector
		{

			template<typename T, glm::length_t L>
			static T getSmallestElement(const glm::vec<L, T>& vector)
			{
				T smallest = vector[0];

				for (glm::length_t i = 1; i < L; ++i) 
				{
					smallest = glm::min(smallest, vector[i]);
				}
				return smallest;
			}

			template<typename T, glm::length_t L>
			static T getLargestElement(const glm::vec<L, T>& vector)
			{
				T largest = vector[0];

				for (glm::length_t i = 1; i < L; ++i)
				{
					largest = glm::max(smallest, vector[i]);
				}
				return largest;
			}

		};

	}

}