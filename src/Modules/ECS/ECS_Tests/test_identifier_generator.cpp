#include "catch_amalgamated.hpp"
#include "IdentifierGenerator.h"

namespace
{
	static constexpr std::uint8_t FIRST_IDENTIFIER_VALUE{ 1 };
	static constexpr std::uint8_t SECOND_IDENTIFIER_VALUE{ 2 };
}

TEST_CASE("Identifier-Generator-Test-001 : IdentifierGenerator is able to generate non-conflicting Identifiers.")
{
	GIVEN("Two identifiers have been generated.")
	{
		ECS_System::IdentifierGenerator::getInstance()->Reset();

		ECS_System::IdentifierType localIdentifierType{ ECS_System::IdentifierType::EntityType };

		ECS_System::IdentifierUnderlyingType localIdentifier_1{ ECS_System::IdentifierGenerator::getInstance()->generateIdentifier(localIdentifierType) };
		ECS_System::IdentifierUnderlyingType localIdentifier_2{ ECS_System::IdentifierGenerator::getInstance()->generateIdentifier(localIdentifierType) };

		THEN("The identifiers should be the sequential rvals 1 and 2.")
		{
			REQUIRE(localIdentifier_1 == FIRST_IDENTIFIER_VALUE);
			REQUIRE(localIdentifier_2 == SECOND_IDENTIFIER_VALUE);
		}
	}
}

TEST_CASE("Identifier-Generator-Test-002 : Identifier is able to generate an Identifier; Reclaim that Identifier and generate that same Identifier.")
{
	GIVEN("An Identifier has been generated.")
	{
		ECS_System::IdentifierGenerator::getInstance()->Reset();

		ECS_System::IdentifierType localIdentifierType{ ECS_System::IdentifierType::EntityType };

		ECS_System::IdentifierUnderlyingType localIdentifier_1{ ECS_System::IdentifierGenerator::getInstance()->generateIdentifier(localIdentifierType) };

		THEN("Reclaim the Identifier.")
		{
			REQUIRE(ECS_System::IdentifierGenerator::getInstance()->reclaimIdentifier(localIdentifierType, localIdentifier_1));
		}
	}
}

TEST_CASE("Identifier-Generator-Test-003 : Identifier is able to be generated, reclaimed and then reused on next generation.")
{
	ECS_System::IdentifierUnderlyingType localIdentifierToTrack{};

	GIVEN("Identifiers have been generated.")
	{
		ECS_System::IdentifierGenerator::getInstance()->Reset();

		ECS_System::IdentifierType localIdentifierType{ ECS_System::IdentifierType::EntityType };

		ECS_System::IdentifierUnderlyingType localIdentifier_1{ ECS_System::IdentifierGenerator::getInstance()->generateIdentifier(localIdentifierType) };
		ECS_System::IdentifierUnderlyingType localIdentifier_2{ ECS_System::IdentifierGenerator::getInstance()->generateIdentifier(localIdentifierType) };
		ECS_System::IdentifierUnderlyingType localIdentifier_3{ ECS_System::IdentifierGenerator::getInstance()->generateIdentifier(localIdentifierType) };
		localIdentifierToTrack = localIdentifier_2;

		THEN("Reclaim the second identifier.")
		{
			REQUIRE(ECS_System::IdentifierGenerator::getInstance()->reclaimIdentifier(localIdentifierType, localIdentifier_2));

			WHEN("A new Identifier is reclaimed it will be equal to the reclaimed Identifier")
			{
				REQUIRE(ECS_System::IdentifierGenerator::getInstance()->generateIdentifier(localIdentifierType) == localIdentifierToTrack);
			}
		}
	}
}