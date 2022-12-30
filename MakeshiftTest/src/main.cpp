// Test environment for Makeshift game engine
// All code here is temporary

#include <Makeshift/Makeshift.hpp>
#include <Makeshift/Level/Level.h>

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

private:
	Makeshift::Level m_Level;

};

int main()
{

	TestEnv tenv;

	tenv.run();

}