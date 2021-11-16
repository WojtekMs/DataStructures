include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG 1a3e2a265f35e604378156cd675b11ef0a184627)
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_ut BSTTest.cpp)
target_link_libraries(${PROJECT_NAME}_ut gtest_main BST_lib)
add_test(NAME BSTTest COMMAND ${PROJECT_NAME}_ut)
