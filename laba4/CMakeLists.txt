cmake_minimum_required(VERSION 3.10)
project(Laba4)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

enable_testing()

add_executable(tests test/test_figures.cpp)
target_link_libraries(tests gtest gtest_main)

add_test(NAME Figures_tests COMMAND tests)