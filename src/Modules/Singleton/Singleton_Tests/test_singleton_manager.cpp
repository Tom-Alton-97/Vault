#define CATCH_CONFIG_MAIN

#include "catch_amalgamated.hpp"
#include "SingletonManager.h"
#include "Singleton.h"



namespace
{
	class TestSingletonType_1 : public Singleton<TestSingletonType_1>
	{
		friend struct std::default_delete<TestSingletonType_1>;
		friend class Singleton<TestSingletonType_1>;

		void destructor() noexcept override {}

		~TestSingletonType_1() = default;
	};

	class TestSingletonType_2 : public Singleton<TestSingletonType_2>
	{
		friend struct std::default_delete<TestSingletonType_2>;
		friend class Singleton<TestSingletonType_2>;

		void destructor() noexcept override {}

		~TestSingletonType_2() = default;
	};

	class TestSingletonType_3 : public Singleton<TestSingletonType_3>
	{
		friend struct std::default_delete<TestSingletonType_3>;
		friend class Singleton<TestSingletonType_3>;

		void destructor() noexcept override {}

		~TestSingletonType_3() = default;
	};

	static std::size_t EMPTY = 0;
}

TEST_CASE("Singleton-Manager-Test-001 : Tests that we can register a singleton and delete the singleton.")
{
	GIVEN("A singleton is created and registered.")
	{
		TestSingletonType_1::getInstance();

		REQUIRE(SingletonManager::getInstance()->singletons.size() == 1);
		REQUIRE(SingletonManager::getInstance()->destructors.size() == 1);

		WHEN("We attempt to delete the singleton.")
		{
			SingletonManager::getInstance()->DestroySingleton(&TestSingletonType_1::getInstance());

			THEN("The singleton shall be removed from the singleton manager")
			{
				REQUIRE(SingletonManager::getInstance()->singletons.size() == EMPTY);
				REQUIRE(SingletonManager::getInstance()->destructors.size() == EMPTY);
			}
		}
	}
}

TEST_CASE("Singleton-Manager-Test-002 : Tests that when we register multiple singletons we can call the DestroyAll to remove all singletons from the manager.")
{
	GIVEN("Two singleton types are registered to the singleton manager.")
	{
		TestSingletonType_2::getInstance();
		TestSingletonType_3::getInstance();

		REQUIRE(SingletonManager::getInstance()->singletons.size() == 2);
		REQUIRE(SingletonManager::getInstance()->destructors.size() == 2);

		WHEN("The singleton manager calls DestroyAll().")
		{
			SingletonManager::getInstance()->DestroyAll();

			THEN("The singleton manager will have destroyed all registered singletons.")
			{
				REQUIRE(SingletonManager::getInstance()->singletons.size() == EMPTY);
				REQUIRE(SingletonManager::getInstance()->destructors.size() == EMPTY);
			}
		}
	}
}