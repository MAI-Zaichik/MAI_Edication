cmake_minimum_required(VERSION 3.14)
project(Laba6)

set(CMAKE_CXX_STANDARD 14)

# Загружаем Google Test через FetchContent (правильная версия)
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
FetchContent_MakeAvailable(googletest)

# Основная библиотека
add_library(Fight_lib src/entilites.cpp)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_include_directories(Fight_lib PUBLIC include)
endif()

# Основное приложение
add_executable(Fight src/main.cpp)
target_link_libraries(Fight Fight_lib)

# Тесты
add_executable(Fight_tests tests/test.cpp)
target_link_libraries(Fight_tests Fight_lib gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(Fight_tests)
enable_testing()