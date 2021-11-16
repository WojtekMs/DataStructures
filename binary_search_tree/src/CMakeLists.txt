add_library(BST_lib INTERFACE)
target_sources(BST_lib PUBLIC BST.hpp NoElementError.hpp)
target_include_directories(BST_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} BST_lib)
