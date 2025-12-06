#include <benchmark/benchmark.h>

#include "Types/EntityManager.h"
#include "Types/ComponentManager.h"
#include "Types/SystemManager.h"
#include "Types/VelocityComponent.h"
#include "Types/VelocitySystem.h"

namespace
{
    static const std::size_t IDENTIFIERS_TO_GENERATE{ 10'000'000 };
}

namespace ECS_System
{
	static void BM_EntityManager_GenerateIdentifiers(benchmark::State& state)
	{
        EntityManager::getInstance().Reset();
        ComponentManager::getInstance().Reset();
        SystemManager::getInstance().Reset();

		for (auto _ : state)
		{
			for (std::size_t i{ 0 }; i < IDENTIFIERS_TO_GENERATE; ++i)
			{
				benchmark::DoNotOptimize(EntityManager::getInstance().generateIdentifier());
			}
		}

		state.SetItemsProcessed(int64_t(state.iterations()) * IDENTIFIERS_TO_GENERATE);
	}

	BENCHMARK(BM_EntityManager_GenerateIdentifiers)->Unit(benchmark::kMillisecond);

    static void BM_EntityManager_MaxIdentifier(benchmark::State& state) 
    {
        EntityManager::getInstance().Reset();
        ComponentManager::getInstance().Reset();
        SystemManager::getInstance().Reset();


        constexpr std::uint64_t testMax = IDENTIFIERS_TO_GENERATE;

        for (std::uint64_t i = 0; i < testMax; ++i) {
            benchmark::DoNotOptimize(EntityManager::getInstance().generateIdentifier());
        }

        for (std::uint64_t i = 0; i < testMax / 2; ++i) {
            benchmark::DoNotOptimize(EntityManager::getInstance().reclaimIdentifier(i + 1));
        }

        for (auto _ : state) {
            for (std::uint64_t i = 0; i < testMax / 2; ++i) {
                benchmark::DoNotOptimize(EntityManager::getInstance().generateIdentifier());
            }
        }

        state.SetItemsProcessed(int64_t(state.iterations()) * (testMax / 2));
    }

    BENCHMARK(BM_EntityManager_MaxIdentifier)->Unit(benchmark::kMillisecond);

    static void BM_Velocity_Update(benchmark::State& state)
    {
        EntityManager::getInstance().Reset();
        ComponentManager::getInstance().Reset();
        SystemManager::getInstance().Reset();

        SystemManager::getInstance().registerSystem<VelocitySystem>();
        ComponentManager::getInstance().registerComponent<VelocityComponent>();

        for (std::size_t i{ 0 }; i < IDENTIFIERS_TO_GENERATE; ++i)
        {
            auto identifier = EntityManager::getInstance().createEntity();
            ComponentManager::getInstance().addComponent<VelocityComponent>(
                identifier, VelocityComponent(0.0f, 0.0f, 0.0f)
            );

            benchmark::DoNotOptimize(
                ComponentManager::getInstance().getComponent<VelocityComponent>(identifier)
            );
        }

        for (auto _ : state)
        {
            SystemManager::getInstance().updateSystems(0.016f);

            benchmark::ClobberMemory();
        }

        state.SetItemsProcessed(int64_t(state.iterations()) * IDENTIFIERS_TO_GENERATE);
    }

    BENCHMARK(BM_Velocity_Update)->Unit(benchmark::kMillisecond);
}

BENCHMARK_MAIN();