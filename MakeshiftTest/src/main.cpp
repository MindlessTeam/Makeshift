// Test environment for Makeshift game engine
// All code here is temporary

#include <Makeshift/Makeshift.hpp>
#include <Makeshift/Debug/Log.h>

#include <Makeshift/Resource/ResourceMap.h>
#include <Makeshift/Resource/Mesh.h>

class TestEnv : public Makeshift::Engine
{

	void init() override
	{

		int ID1 = rmap.loadResource<Makeshift::Mesh>("content/mdl/test");
		DEBUG_INFO("First ID: {}", ID1);

		int ID2 = rmap.loadResource<Makeshift::Mesh>("content/mdl/test");
		DEBUG_INFO("Second ID: {}", ID2);

		DEBUG_INFO("Mesh 1: {}, {}",
			((Makeshift::Mesh*)rmap.getResource(ID1).get())->getData().vertices.size(),
			((Makeshift::Mesh*)rmap.getResource(ID1).get())->getData().indices.size());

		DEBUG_INFO("Mesh 2: {}, {}",
			((Makeshift::Mesh*)rmap.getResource(ID2).get())->getData().vertices.size(),
			((Makeshift::Mesh*)rmap.getResource(ID2).get())->getData().indices.size());

		// I mean...
		// this system works, but it's horrible to use.
		// This will have to change!
		// 
		// The problem I am currently facing is that I
		// want to have a virtual base class for resources
		// but that WILL NOT work with the current rework idea
		// I have in mind.
		// 
		// That idea being: 
		// A template ResourceMap class!
		// I would only have to take care of <T> pointers
		// which would save me the trouble of the mess
		// above, but it doesn't allow for a Resource
		// base class. hrmpf!

	}

	void update() override
	{

	}

	void cleanUp() override
	{

	}

	Makeshift::ResourceMap rmap;

};

int main()
{

	TestEnv testenv;

	testenv.run();

}