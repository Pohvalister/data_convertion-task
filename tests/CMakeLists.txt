project(Saber_test)

cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(./googletest)

add_executable(run_tests
        run_tests.cpp
        ../1_int_to_bin.h
        ../2_remove_dups.h
        ../3_list_serializing.h
        ../3_list_serializing.cpp
        )
target_link_libraries(run_tests gtest gtest_main)

