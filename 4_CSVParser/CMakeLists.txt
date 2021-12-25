cmake_minimum_required(VERSION 3.19)
project(4_CSVParser)

set(CMAKE_CXX_STANDARD 20)

add_executable(4_CSVParser main.cpp Common/Common.h CSVParser/CSVParser.cpp CSVParser/CSVParser.h)