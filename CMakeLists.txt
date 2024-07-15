cmake_minimum_required(VERSION 3.15)
project(memory_pool)

set(CMAKE_CXX_STANDARD 17)

# Release mode
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 -pthread")


INCLUDE_DIRECTORIES(include)

# Debug mode
# set(CMAKE_BUILD_TYPE Debug)

add_executable(memory_pool
    src/main.cpp 
    src/memory_pool.cpp
    src/mem_pool_manager.cpp)