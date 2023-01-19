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

		std::shared_ptr<Makeshift::Mesh> m1 = rmap.getResource<Makeshift::Mesh>(ID1);
		DEBUG_INFO("Mesh 1: {}, {}", m1->getData().vertices.size(), m1->getData().indices.size());
		
		std::shared_ptr<Makeshift::Mesh> m2 = rmap.getResource<Makeshift::Mesh>(ID2);
		DEBUG_INFO("Mesh 2: {}, {}", m2->getData().vertices.size(), m2->getData().indices.size());

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