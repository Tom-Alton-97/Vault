#include <benchmark/benchmark.h>
#include "Types/ManagerBase.h"

namespace ECS_System
{
	static void BM_EntityManager_GenerateIdentifiers(benchmark::State& state)
	{
		ManagerBase::getInstance().Reset();

		for (auto _ : state)
		{
			for (std::size_t i{ 0 }; i < 1'000'000; ++i)
			{
				benchmark::DoNotOptimize(ManagerBase::getInstance().generateIdentifier());
			}
		}

		state.SetItemsProcessed(int64_t(state.iterations()) * 1'000'000);
	}

	BENCHMARK(BM_EntityManager_GenerateIdentifiers)->Unit(benchmark::kMillisecond);

    static void BM_EntityManager_MaxIdentifier(benchmark::State& state) {
        ManagerBase& mgr = ManagerBase::getInstance();
        mgr.Reset();

        // Temporarily set a small "max" for testing
        constexpr std::uint64_t testMax = 1'000'000; // instead of full uint64 max

        // Pre-fill identifiers up to testMax
        for (std::uint64_t i = 0; i < testMax; ++i) {
            benchmark::DoNotOptimize(mgr.generateIdentifier());
        }

        // Reclaim half of them
        for (std::uint64_t i = 0; i < testMax / 2; ++i) {
            benchmark::DoNotOptimize(mgr.reclaimIdentifier(i + 1));
        }

        for (auto _ : state) {
            // Generate reclaimed IDs (should come from reclaimed pool)
            for (std::uint64_t i = 0; i < testMax / 2; ++i) {
                benchmark::DoNotOptimize(mgr.generateIdentifier());
            }
        }

        state.SetItemsProcessed(int64_t(state.iterations()) * (testMax / 2));
    }

    BENCHMARK(BM_EntityManager_MaxIdentifier)->Unit(benchmark::kMillisecond);
}

BENCHMARK_MAIN();

