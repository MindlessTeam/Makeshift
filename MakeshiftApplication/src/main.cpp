// ----------------------------------------------
// Copyright (c) 2022-2024 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#include <Makeshift/Makeshift.hpp>

#include <clientAPI.h>

class MakeshiftApp : public Makeshift::Engine
{

	void init() override
	{
		Client::initLog();
		Client::registerEntities();
		

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

	MakeshiftApp app;
	app.run();

}