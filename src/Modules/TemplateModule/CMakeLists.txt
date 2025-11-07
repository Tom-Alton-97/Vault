cmake_minimum_required(VERSION 3.31)

file(GLOB MODULE_SOURCES CMAKE_CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

#remove module 1 with the intended module name
add_library(TemplateModule STATIC TemplateModule.cpp TemplateModule.h)

target_include_directories(TemplateModule PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})