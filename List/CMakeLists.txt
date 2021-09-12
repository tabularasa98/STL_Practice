cmake_minimum_required(VERSION 3.16)
project(Assignment2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment2
        List.h
        test_list.cpp List.hpp)
