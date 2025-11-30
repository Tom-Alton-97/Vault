file(GLOB_RECURSE BENCH_SOURCES CONFIGURE_DEPENDS *.cpp *.h)
add_executable(ECS_Benchmarks ${BENCH_SOURCES})
target_link_libraries(ECS_Benchmarks PRIVATE ECS benchmark::benchmark)
target_include_directories(ECS_Benchmarks PRIVATE ${CMAKE_SOURCE_DIR}/src/Modules/ECS)

target_compile_features(ECS_Benchmarks PRIVATE cxx_std_23)

set_target_properties(ECS_Benchmarks PROPERTIES
    CMAKE_BUILD_TYPE Release
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/Release
)