cmake_minimum_required(VERSION 3.10)
project(Saber_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(Test_Main
        1_int_to_bin.h
        2_remove_dups.h
        3_list_serializing.h
        3_list_serializing.cpp
        main.cpp
        )

add_subdirectory(tests)
