#include "catch_amalgamated.hpp"
#include "SystemManager.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "VelocityComponent.h"
#include "VelocitySystem.h"

namespace
{
    class TestSystemA : public ECS_System::SystemBase
    {
    public:
        std::uint_fast8_t updateCount{ 0 };

        void update(float argDeltaTime) override
        {
            updateCount++;
        }
    };

    class TestSystemB : public ECS_System::SystemBase
    {
    public:
        std::uint_fast8_t updateCount{ 0 };

        void update(float argDeltaTime) override
        {
            updateCount+=2;
        }
    };

    static constexpr float SYSTEM_A_EXPECTED_UPDATE_VALUE{ 1 };
    static constexpr float SYSTEM_B_EXPECTED_UPDATE_VALUE{ 2 };

}

TEST_CASE("System-Manager-Test-001 : Register a system and retrieve it.")
{
    GIVEN("A System Manager is created.")
    {
        ECS_System::SystemManager::getInstance().Reset();
        ECS_System::SystemManager::getInstance();

        WHEN("A system is registered to the manager.")
        {
            auto& systemPtr = ECS_System::SystemManager::getInstance().registerSystem<TestSystemA>(); // TODO maybe a pointer

            THEN("We are able to retrieve the registered system.")
            {
                REQUIRE(ECS_System::SystemManager::getInstance().getSystem<TestSystemA>() == &systemPtr);
            }
        }
    }
}

TEST_CASE("System-Manager-Test-002 : Register and update a single system.")
{
    GIVEN("A System Manager is created.")
    {
        ECS_System::SystemManager::getInstance().Reset();
        ECS_System::SystemManager::getInstance();

        WHEN("A system is registered.")
        {
            auto& systemRef = ECS_System::SystemManager::getInstance().registerSystem<TestSystemA>();

            THEN("Retrieve the system.")
            {
                REQUIRE(ECS_System::SystemManager::getInstance().getSystem<TestSystemA>() == &systemRef);
            }
        }
    }
}

TEST_CASE("System-Manager-Test-003 : Register a system to the manger and clear the managers systems.")
{
    GIVEN("A System Manager is created.")
    {
        ECS_System::SystemManager::getInstance().Reset();
        ECS_System::SystemManager::getInstance();
        
        WHEN("A system is registered.")
        {
            auto& systemRef = ECS_System::SystemManager::getInstance().registerSystem<TestSystemA>();

            REQUIRE(ECS_System::SystemManager::getInstance().getSystem<TestSystemA>() == &systemRef);

            THEN("Clear the system manager")
            {
                ECS_System::SystemManager::getInstance().Reset();

                REQUIRE(nullptr == ECS_System::SystemManager::getInstance().getSystem<TestSystemA>());
            }
        }
    }
}

TEST_CASE("System-Manager-Test-004 : Register multiple systems of a different type.")
{
    GIVEN("A System Manager is created.")
    {
        ECS_System::SystemManager::getInstance().Reset();
        ECS_System::SystemManager::getInstance();
 
        WHEN("Two differing systems are registered to the manager.")
        {
            auto& systemRefA = ECS_System::SystemManager::getInstance().registerSystem<TestSystemA>();
            auto& systemRefB = ECS_System::SystemManager::getInstance().registerSystem<TestSystemB>();

            REQUIRE(ECS_System::SystemManager::getInstance().getSystem<TestSystemA>() == &systemRefA);
            REQUIRE(ECS_System::SystemManager::getInstance().getSystem<TestSystemB>() == &systemRefB);

            THEN("Resetting the system manager shall remove the registered systems.")
            {
                ECS_System::SystemManager::getInstance().Reset();

                REQUIRE(nullptr == ECS_System::SystemManager::getInstance().getSystem<TestSystemA>());
                REQUIRE(nullptr == ECS_System::SystemManager::getInstance().getSystem<TestSystemB>());
            }
        }
    }
}

TEST_CASE("System-Manager-Test-005 : Register and update a single system.")
{
    GIVEN("A System Manager is created.")
    {
        ECS_System::SystemManager::getInstance().Reset();
        ECS_System::SystemManager::getInstance();

        WHEN("A single system is registered to the manager.")
        {
            auto& systemRefA = ECS_System::SystemManager::getInstance().registerSystem<TestSystemA>();
            
            REQUIRE(ECS_System::SystemManager::getInstance().getSystem<TestSystemA>() == &systemRefA);

            THEN("Request the system manager to update a system.")
            {
                ECS_System::SystemManager::getInstance().updateSystem<TestSystemA>(0.1f);
                
                REQUIRE(systemRefA.updateCount == SYSTEM_A_EXPECTED_UPDATE_VALUE);
            }
        }
    }
}

TEST_CASE("System-Manager-Test-006 : Register and update multiple systems.")
{
    GIVEN("A System Manager is created.")
    {
        ECS_System::SystemManager::getInstance().Reset();
        ECS_System::SystemManager::getInstance();

        WHEN("Two differing systems are registered to the manager.")
        {
            auto& systemRefA = ECS_System::SystemManager::getInstance().registerSystem<TestSystemA>();
            auto& systemRefB = ECS_System::SystemManager::getInstance().registerSystem<TestSystemB>();

            REQUIRE(ECS_System::SystemManager::getInstance().getSystem<TestSystemA>() == &systemRefA);
            REQUIRE(ECS_System::SystemManager::getInstance().getSystem<TestSystemB>() == &systemRefB);

            THEN("Request the system manager to update the registered systems.")
            {
                ECS_System::SystemManager::getInstance().updateSystems(0.1f);

                REQUIRE(systemRefA.updateCount == SYSTEM_A_EXPECTED_UPDATE_VALUE);
                REQUIRE(systemRefB.updateCount == SYSTEM_B_EXPECTED_UPDATE_VALUE);
            }
        }
    }
}

TEST_CASE("System-Manager-Test-007 : Register two entities with a component and update both.")
{
    GIVEN("A System Manager is created.")
    {
        ECS_System::SystemManager::getInstance().Reset();
        ECS_System::EntityManager::getInstance().Reset();
        ECS_System::ComponentManager::getInstance().Reset();
        ECS_System::SystemManager::getInstance();
        ECS_System::EntityManager::getInstance();
        ECS_System::ComponentManager::getInstance();

        WHEN("Register a system to the manager.")
        {
            auto& velocitySystem = ECS_System::SystemManager::getInstance().registerSystem<ECS_System::VelocitySystem>();
            REQUIRE(ECS_System::SystemManager::getInstance().getSystem<ECS_System::VelocitySystem>() == &velocitySystem);

            AND_WHEN("Register two entities with a common component.")
            {
                ECS_System::ComponentManager::getInstance().registerComponent<ECS_System::VelocityComponent>();

                auto entity1 = ECS_System::EntityManager::getInstance().createEntity();
                auto entity2 = ECS_System::EntityManager::getInstance().createEntity();

                ECS_System::ComponentManager::getInstance().addComponent<ECS_System::VelocityComponent>(
                    entity1, ECS_System::VelocityComponent( 1.0f, 1.0f, 1.0f )
                );
                ECS_System::ComponentManager::getInstance().addComponent<ECS_System::VelocityComponent>(
                    entity2, ECS_System::VelocityComponent{ 4.0f, 4.0f, 4.0f }
                );

                THEN("Update the systems.")
                {
                    ECS_System::SystemManager::getInstance().updateSystems(1.0f);
                    auto& vel1 = ECS_System::ComponentManager::getInstance().getComponent<ECS_System::VelocityComponent>(entity1);
                    auto& vel2 = ECS_System::ComponentManager::getInstance().getComponent<ECS_System::VelocityComponent>(entity2);

                    REQUIRE(vel1.x == 3.0f);
                    REQUIRE(vel1.y == 3.0f);
                    REQUIRE(vel1.z == 3.0f);
                    REQUIRE(vel2.x == 6.0f);
                    REQUIRE(vel2.y == 6.0f);
                    REQUIRE(vel2.z == 6.0f);
                }
            }
        }
    }
}