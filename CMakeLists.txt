cmake_minimum_required(VERSION 3.18)

project(DataStructures CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(BuildType)
set_default_build_type()

enable_testing()
add_subdirectory(binary_search_tree EXCLUDE_FROM_ALL)
add_subdirectory(forward_list EXCLUDE_FROM_ALL)
