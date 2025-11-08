#define CATCH_CONFIG_MAIN

#include "catch_amalgamated.hpp"

#include "Entity.h"
#include "ECS_Tests_Utility.h"
#include "EntityActiveStatus.h"

TEST_CASE("Entity-Test-001 : Create an Entity with arbitrary ID and check that it has been assigned correctly.") 
{
    GIVEN("An entity has been created with an arbitrary ID.")
    {
        EntityID testEntityID{ Tests_Utility::ECS_Tests_Utility::getInstance().getUnusedEntityIdentifier() };
        Entity testEntity(testEntityID);

        THEN("Check that the entity identifier was set correctly.")
        {
            REQUIRE(testEntityID == testEntity.getEntityID());
        }
    }
}
//
//TEST_CASE("Entity-Test-002 : Create an Entity with an ID and check that the EntityActiveStatus is defaulted correctly")
//{
//    GIVEN("An entity has been created")
//    {
//        Entity testEntity(Tests_Utility::ECS_Tests_Utility::getUnusedArbitraryIdentifier());
//
//        THEN("Check that the EntityActiveStatus is defaulted to" + EntityActiveStatus)
//        {
//
//        }
//    }
//}
//
//TEST_CASE("ARST")
//{
//    EntityActiveStatus<std::uint_fast8_t> status{ test };
//}