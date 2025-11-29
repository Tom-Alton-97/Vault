#define CATCH_CONFIG_MAIN

#include "catch_amalgamated.hpp"
#include "SingletonManager.h"
#include "Singleton.h"

class TestSingletonType : public Singleton<TestSingletonType>
{
	friend class Singleton<TestSingletonType>;
	friend struct std::default_delete<TestSingletonType>;

	void destructor() noexcept override
	{
		
	}

	~TestSingletonType() = default;
};

TEST_CASE("Singleton-Manager-Test-001 : test")
{
	TestSingletonType::getInstance();

	REQUIRE(SingletonManager::getInstance()->singletons.size() == 1);
	REQUIRE(SingletonManager::getInstance()->destructors.size() == 1);

	SingletonManager::getInstance()->DeleteSingleton(&TestSingletonType::getInstance());

	REQUIRE(SingletonManager::getInstance()->singletons.size() == 0);
	REQUIRE(SingletonManager::getInstance()->destructors.size() == 0);
}

// test destroy all
// test register
// test 