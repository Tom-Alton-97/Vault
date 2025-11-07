cmake -S . -B out/build/x64-debug
cmake -S . -B out/build/x64-debug -DBUILD_TESTS=ON
cmake --build out/build/x64-debug