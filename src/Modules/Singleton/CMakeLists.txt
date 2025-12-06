cmake_minimum_required(VERSION 3.31)

file(GLOB_RECURSE MODULE_SOURCES CMAKE_CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

list(FILTER MODULE_SOURCES EXCLUDE REGEX ".*/Singleton_Tests/.*")

add_library(Singleton STATIC ${MODULE_SOURCES})
target_include_directories(Singleton PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTS)
	add_subdirectory(Singleton_Tests)
endif()