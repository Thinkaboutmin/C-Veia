cmake_minimum_required(VERSION 3.17)
project(ticTacToe)

set(CMAKE_CXX_STANDARD 20)

add_executable(ticTacToe src/plain_table.cpp src/plain_table.hpp src/string_table.cpp src/string_table.hpp)