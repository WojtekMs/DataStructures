add_library(${PROJECT_NAME}_lib Trie.cpp)
add_executable(${PROJECT_NAME}_exe main.cpp)

target_link_libraries(${PROJECT_NAME}_exe ${PROJECT_NAME}_lib)
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})