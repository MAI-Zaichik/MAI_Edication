enable_testing()

add_subdirectory(../googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

add_executable(ToTurkish_tests Tests.cpp)
target_link_libraries(ToTurkish_tests ToTurkish_lib gtest gtest_main)


add_test(NAME TurkishNumberTests COMMAND ToTurkish_tests)