cmake_minimum_required(VERSION 3.28)
project(sheet10)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Add the executable
add_executable(sheet10 main.cpp
        src/UnrolledLinkedList.cpp
        src/TieredArray.cpp)
