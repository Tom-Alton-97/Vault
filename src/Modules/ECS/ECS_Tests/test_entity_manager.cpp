#include "catch_amalgamated.hpp"
#include "EntityManager.h"

namespace
{
	static constexpr std::uint8_t FIRST_IDENTIFIER_VALUE{ 1 };
	static constexpr std::uint8_t SECOND_IDENTIFIER_VALUE{ 2 };
}

TEST_CASE("Entity-Manager-Test-001 : Entity Manager is able to generate to unique identifiers")
{
	GIVEN("Two identifiers have been generated.")
	{
		ECS_System::EntityManager::getInstance().Reset();

		ECS_System::IdentifierUnderlyingType localIdentifier_1{ ECS_System::EntityManager::getInstance().createEntity()};
		ECS_System::IdentifierUnderlyingType localIdentifier_2{ ECS_System::EntityManager::getInstance().createEntity()};

		THEN("The identifiers should be the sequential rvals 1 and 2.")
		{
			REQUIRE(localIdentifier_1 == FIRST_IDENTIFIER_VALUE);
			REQUIRE(localIdentifier_2 == SECOND_IDENTIFIER_VALUE);
		}
	}
}