cmake_minimum_required(VERSION 3.19)
project(1_HashTable)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(1_HashTable
        HashTable.cpp
        HashTable.h
        main.cpp)
