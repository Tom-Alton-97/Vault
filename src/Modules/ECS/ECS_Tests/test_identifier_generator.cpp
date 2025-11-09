#include "catch_amalgamated.hpp"
#include "IdentifierGenerator.h"

TEST_CASE("Identifier-Generator-Test-001 : IdentifierGenerator is able to generate non-conflicting Identifiers.")
{
	GIVEN("Two identifiers have been generated.")
	{
		ECS_System::IdentifierType localIdentifierType{ ECS_System::IdentifierType::EntityType };

		ECS_System::IdentifierUnderlyingType localIdentifier_1{ ECS_System::IdentifierGenerator::getInstance()->generateIdentifier(localIdentifierType) };
		ECS_System::IdentifierUnderlyingType localIdentifier_2{ ECS_System::IdentifierGenerator::getInstance()->generateIdentifier(localIdentifierType) };

		THEN("The identifiers should be the sequential rvals 1 and 2.")
		{
			REQUIRE(localIdentifier_1 == 1);
			REQUIRE(localIdentifier_2 == 2);
		}
	}
}