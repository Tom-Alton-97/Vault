file(GLOB MODULE_DIRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} Modules/*)

foreach(MODULE_NAME ${MODULE_DIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Modules/${MODULE_NAME})
        message(STATUS "Adding module: ${MODULE_NAME}")
        add_subdirectory(Modules/${MODULE_NAME})
    endif()
endforeach()

add_executable(Main main.cpp)

target_include_directories(Main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Modules)

foreach(MODULE_NAME ${MODULE_DIRS})
    if(IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Modules/${MODULE_NAME})
        target_link_libraries(Main PRIVATE ${MODULE_NAME})
    endif()
endforeach()

if(BUILD_TESTS)
    add_subdirectory(Test)
endif()