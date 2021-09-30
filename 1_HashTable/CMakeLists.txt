cmake_minimum_required(VERSION 3.19)
project(HashTable_project)

set(CMAKE_CXX_STANDARD 14)

set(PROJECT_FILES HashTable.h HashTable.cpp)
set(UNIT_TESTS tests/test.cpp)
set(MAIN_FILE main.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(.)
enable_testing()

# Add my HashTable as library
add_library(HashTable ${PROJECT_FILES})

# Unit tests
add_executable(unit_tests ${UNIT_TESTS})

# If need to add some 'main' functional to this project
add_executable(HashTable_main ${MAIN_FILE})

# link executable with my HashTable
target_link_libraries(unit_tests HashTable gtest_main)
target_link_libraries(HashTable_main HashTable)

include(GoogleTest)
gtest_discover_tests(unit_tests)