cmake -S . -B out/build/x64-debug
cmake -S . -B out/build/x64-debug -DBUILD_TESTS=ON

cmake -S . -B out/build/x64-release -DBUILD_BENCHMARK_TESTS=ON -DBENCHMARK_ENABLE_TESTING=OFF
cmake --build out/build/x64-release --target ECS ECS_Benchmarks

cmake --build out/build/x64-debug
cmake -S . -B out/build/x64-debug -DBUILD_TESTS=ON -DBUILD_BENCHMARK_TESTS=ON -DBENCHMARK_ENABLE_TESTING=OFF

//////////

GOOGLE BENCHMARK

cd external/benchmark
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_TESTING=OFF -DBENCHMARK_USE_BUNDLED_GTEST=OFF ..
cmake --build . --target benchmark

/////////