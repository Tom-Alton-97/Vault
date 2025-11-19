file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS 
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(Singleton_Tests ${TEST_SOURCES} ${CMAKE_SOURCE_DIR}/external/catch2/catch_amalgamated.cpp)

target_include_directories(Singleton_Tests PRIVATE
    ${CMAKE_SOURCE_DIR}/external/catch2
    ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_link_libraries(Singleton_Tests PRIVATE Singleton)

add_test(NAME Singleton_Tests COMMAND Singleton_Tests)