file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(ECS_Tests
    ${TEST_SOURCES}
    ${CMAKE_SOURCE_DIR}/external/catch2/catch_amalgamated.cpp
)

target_include_directories(ECS_Tests PRIVATE
    ${CMAKE_SOURCE_DIR}/external/catch2
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../Types
)

target_link_libraries(ECS_Tests PRIVATE ECS)

add_test(NAME ECS_Tests COMMAND ECS_Tests)