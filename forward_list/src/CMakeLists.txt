add_library(${PROJECT_NAME}_lib INTERFACE)
target_sources(${PROJECT_NAME}_lib PUBLIC ForwardList.hpp)
target_include_directories(${PROJECT_NAME}_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME}_exe main.cpp)
target_link_libraries(${PROJECT_NAME}_exe ${PROJECT_NAME}_lib)
