enable_testing()

add_subdirectory(../googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

add_executable(DecimalTests Tests.cpp)

target_link_libraries(DecimalTests Decimal_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(DecimalTests)