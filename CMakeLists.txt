cmake_minimum_required(VERSION 3.21)
project(aoc2021)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.76)

include_directories(Boost::boost)

add_subdirectory(01)
