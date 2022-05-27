project(Saber_test)

cmake_minimum_required(VERSION 3.10)

add_subdirectory(./googletest)

add_executable(run_tests
        run_tests.cpp
        )

target_link_libraries(run_tests gtest gtest_main)