#include <benchmark/benchmark.h>
#include "Types/ManagerBase.h"

namespace
{
    static const std::size_t IDENTIFIERS_TO_GENERATE{ 10'000'000 };
}

namespace ECS_System
{
	static void BM_EntityManager_GenerateIdentifiers(benchmark::State& state)
	{
		ManagerBase::getInstance().Reset();

		for (auto _ : state)
		{
			for (std::size_t i{ 0 }; i < IDENTIFIERS_TO_GENERATE; ++i)
			{
				benchmark::DoNotOptimize(ManagerBase::getInstance().generateIdentifier());
			}
		}

		state.SetItemsProcessed(int64_t(state.iterations()) * IDENTIFIERS_TO_GENERATE);
	}

	BENCHMARK(BM_EntityManager_GenerateIdentifiers)->Unit(benchmark::kMillisecond);

    static void BM_EntityManager_MaxIdentifier(benchmark::State& state) {
        ManagerBase::getInstance().Reset();

        // Temporarily set a small "max" for testing
        constexpr std::uint64_t testMax = IDENTIFIERS_TO_GENERATE; // instead of full uint64 max

        // Pre-fill identifiers up to testMax
        for (std::uint64_t i = 0; i < testMax; ++i) {
            benchmark::DoNotOptimize(ManagerBase::getInstance().generateIdentifier());
        }

        // Reclaim half of them
        for (std::uint64_t i = 0; i < testMax / 2; ++i) {
            benchmark::DoNotOptimize(ManagerBase::getInstance().reclaimIdentifier(i + 1));
        }

        for (auto _ : state) {
            // Generate reclaimed IDs (should come from reclaimed pool)
            for (std::uint64_t i = 0; i < testMax / 2; ++i) {
                benchmark::DoNotOptimize(ManagerBase::getInstance().generateIdentifier());
            }
        }

        state.SetItemsProcessed(int64_t(state.iterations()) * (testMax / 2));
    }

    BENCHMARK(BM_EntityManager_MaxIdentifier)->Unit(benchmark::kMillisecond);
}

BENCHMARK_MAIN();

