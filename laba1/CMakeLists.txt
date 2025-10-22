cmake_minimum_required(VERSION 3.14)
project(Laba1)

set(CMAKE_CXX_STANDARD 11)

# Основная библиотека
add_library(ToTurkish_lib src/ToTurkish.cpp)

# Основное приложение
add_executable(TurkishConverter src/main.cpp)
target_link_libraries(TurkishConverter ToTurkish_lib)

# Тесты
add_subdirectory(tests)