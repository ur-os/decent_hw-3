cmake_minimum_required(VERSION 3.17)
project(decent_hw_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(decent_hw_3 main.cpp
        shared_scheme.cpp
        shared_scheme.h
        utils.cpp
        utils.h
        )
target_link_libraries(decent_hw_3 cryptopp)
