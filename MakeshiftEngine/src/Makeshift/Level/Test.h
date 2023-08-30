// ----------------------------------------------
// Copyright (c) 2022-2023 Aaron Kerker
// MIT-Licensed: https://opensource.org/licenses/MIT
// ----------------------------------------------

#pragma once

#include "Entity.h"

#include "Makeshift/Debug/Log.h"

#include "Makeshift/Resource/Test.h"

namespace Makeshift
{

	// Test
	// -----------------------------------------
	// Test Entity
	class Test : public Entity
	{

	public:
		virtual void serialize(Json::Value& value) override
		{
			DEBUG_TRACE("Makeshift::Test::serialize()");
			
			Json::Value vectorNode;
			vectorNode["x"] = 2;
			vectorNode["y"] = 3;
			vectorNode["z"] = 17;

			value["testVector"] = vectorNode;

			value["testString"] = "Lorem ipsum dolor sit amet.";
			value["testFloat"] = 13.25f;

		}
		virtual void deSerialize(Json::Value value) override {

			const Json::Value& vectorNode = value["testVector"];
			int x = vectorNode["x"].asInt();
			int y = vectorNode["y"].asInt();
			int z = vectorNode["z"].asInt();

			std::string testString = value["testString"].asString();
			float testFloat = value["testFloat"].asFloat();

			// Print the deserialized values
			DEBUG_INFO("testVector: x = {}, y = {}, z = {}", x, y, z);
			DEBUG_INFO("testString: {}", testString);
			DEBUG_INFO("testFloat: {}", testFloat);

		}

	public:
		virtual std::string getName() override
		{
			return "Test";
		}

	protected:
		virtual void onInit() override 
		{
			m_TestRes = Engine::getInstance().getResourceMap()->addResource<TestRes>("TestResRes");
		}
		virtual void onUpdate() override {}

		virtual void onEnable() override {}
		virtual void onDisable() override {}

	private:
		std::shared_ptr<TestRes> m_TestRes;

	};

}
