cmake_minimum_required(VERSION 3.14)

project(Laba2)

set(CMAKE_CXX_STANDARD 14)
include_directories(include)

add_library(Decimal_lib src/realisation.cpp)

add_executable(Laba2 src/main.cpp)
target_link_libraries(Laba2 Decimal_lib)

add_subdirectory(tests)