cmake_minimum_required(VERSION 3.31)

file(GLOB MODULE_SOURCES CMAKE_CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(Logging STATIC Logging.cpp Logging.h)
target_include_directories(Logging PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})