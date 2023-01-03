// Test environment for Makeshift game engine
// All code here is temporary

#include <Makeshift/Makeshift.hpp>
#include <Makeshift/Debug/Log.h>

class TestEnv : public Makeshift::Engine
{

	void init() override
	{

	}

	void update() override
	{

	}

	void cleanUp() override
	{

	}

};

int main()
{

	TestEnv testenv;

	testenv.run();

}