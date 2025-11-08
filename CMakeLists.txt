cmake_minimum_required(VERSION 3.31)
project(Vault LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" OFF)

file(GLOB MODULE_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules/*
)
foreach(MODULE ${MODULE_DIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/Modules/${MODULE})
        add_subdirectory(src/Modules/${MODULE})
    endif()
endforeach()

add_executable(Main src/main.cpp "src/Modules/Singleton/Singleton.h")
target_link_libraries(Main PRIVATE ECS)
target_include_directories(Main PRIVATE src/Modules/ECS)