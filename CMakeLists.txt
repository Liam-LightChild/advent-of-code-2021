cmake_minimum_required(VERSION 3.21)
project(aoc2021)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.76)

include_directories(Boost::boost)

add_subdirectory(01)
add_subdirectory(02)
add_subdirectory(03)
add_subdirectory(05)
add_subdirectory(06)
add_subdirectory(07)
add_subdirectory(08)
add_subdirectory(09)
add_subdirectory(10)
