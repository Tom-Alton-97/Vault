#define CATCH_CONFIG_MAIN

#include "catch_amalgamated.hpp"

#include "ECS_Tests_Utility.h"
#include "Entity.h"

TEST_CASE("Entity-Test-001 : Create an Entity with arbitrary ID and check that it has been assigned correctly.")
{
	GIVEN("An Entity has been created with an arbitrary ID.")
	{
		ECS_System::EntityID testEntityID{ Tests_Utility::ECS_Tests_Utility::getInstance().getUnusedEntityIdentifier() };
		ECS_System::Entity testEntity(testEntityID);

		THEN("Check that the entity identifier was set correctly.")
		{
			REQUIRE(testEntityID == testEntity.getEntityID());
		}
	}
}

TEST_CASE("Entity-Test-002 : Create an Entity with an ID and check that the EntityActiveStatus is defaulted correctly")
{
	GIVEN("An Entity has been created with an arbitrary ID.")
	{
		ECS_System::EntityID testEntityID{ Tests_Utility::ECS_Tests_Utility::getInstance().getUnusedEntityIdentifier() };
		ECS_System::Entity testEntity(testEntityID);

		THEN("Check that the EntityActiveStatus is defaulted to Disabled")
		{
			REQUIRE(testEntity.getEntityStatus() == ECS_System::EntityActiveStatus::EntityEnabled);
		}
	}
}

TEST_CASE("Entity-Test-003 : Create an Entity with an ID and check that we can set the EntityActiveStatus to EntityDisabled")
{
	GIVEN("An Entity has been created")
	{
		ECS_System::EntityID testEntityID{ Tests_Utility::ECS_Tests_Utility::getInstance().getUnusedEntityIdentifier() };
		ECS_System::Entity testEntity(testEntityID);

		WHEN("Set the Entities EntityActiveStatus to EntityDisabled")
		{
			testEntity.setEntityStatusDisabled();

			THEN("Check that the Entities EntityActiveStatus is set to EntityDisabled")
			{
				REQUIRE(testEntity.getEntityStatus() == ECS_System::EntityActiveStatus::EntityDisabled);
			}
		}
	}
}

TEST_CASE("Entity-Test-004 : Create an Entity with an ID and check that we can set the EntityActiveStatus to EntityEnabled")
{
	GIVEN("An Entity has been created")
	{
		ECS_System::EntityID testEntityID{ Tests_Utility::ECS_Tests_Utility::getInstance().getUnusedEntityIdentifier() };
		ECS_System::Entity testEntity(testEntityID);

		WHEN("Set the Entities EntityActiveStatus to EntityDisabled")
		{
			testEntity.setEntityStatusDisabled();

			REQUIRE(testEntity.getEntityStatus() == ECS_System::EntityActiveStatus::EntityDisabled);

			THEN("Set the EntitiesActiveStatus to EntityEnabled")
			{
				testEntity.setEntityStatusEnabled();

				REQUIRE(testEntity.getEntityStatus() == ECS_System::EntityActiveStatus::EntityEnabled);
			}
		}
	}
}