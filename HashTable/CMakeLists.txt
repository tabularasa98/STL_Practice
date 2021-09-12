cmake_minimum_required(VERSION 3.15)
project(Assignment5)

set(CMAKE_CXX_STANDARD 14)

include_directories(provided)

add_executable(Assignment5
        provided/hashtable.h
        provided/hashtable.hpp
        provided/proj5.cpp
        provided/proj5.x
        provided/proj5_provided.tar
        #provided/scrypt.cpp
        provided/scrypt.x
        provided/sproj5.x
        provided/test1
        provided/passserver.h provided/passserver.hpp sproj5.cpp)
