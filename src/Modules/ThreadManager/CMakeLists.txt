cmake_minimum_required(VERSION 3.31)

file(GLOB MODULE_SOURCES CMAKE_CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(ThreadManager STATIC ThreadManager.cpp ThreadManager.h)
target_include_directories(ThreadManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})