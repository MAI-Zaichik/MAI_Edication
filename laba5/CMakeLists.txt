cmake_minimum_required(VERSION 3.10)
project(Laba5)

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

add_executable(${CMAKE_PROJECT_NAME}
    src/main.cpp
    src/mem_res.cpp
)

enable_testing()

add_executable(Vector_tests
    tests/test.cpp
    src/mem_res.cpp
)

target_link_libraries(Vector_tests gtest gtest_main)

add_test(NAME Vector_tests COMMAND test)