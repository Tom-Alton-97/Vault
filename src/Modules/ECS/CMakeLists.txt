cmake_minimum_required(VERSION 3.31)

file(GLOB_RECURSE MODULE_SOURCES CMAKE_CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

list(FILTER MODULE_SOURCES EXCLUDE REGEX ".*/ECS_Tests/.*")

add_library(ECS STATIC ${MODULE_SOURCES})
target_include_directories(ECS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ECS PUBLIC Singleton)


if(BUILD_TESTS)
	add_subdirectory(ECS_Tests)
endif()