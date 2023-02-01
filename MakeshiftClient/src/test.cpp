// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include "test.h"

#include <iostream>

namespace Client
{

	void DLLTest::printSomething()
	{
		std::cout << "This is a message from the Client!" << std::endl;
	}

}