cmake_minimum_required(VERSION 3.13)

project(BST)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
