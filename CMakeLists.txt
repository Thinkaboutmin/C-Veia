cmake_minimum_required(VERSION 3.17)
project(ticTacToe)

set(CMAKE_CXX_STANDARD 20)

add_executable(ticTacToe src/lib/plain_table.cpp src/lib/plain_table.hpp src/lib/string_table.cpp src/lib/string_table.hpp src/exceptions/table/table_exceptions.h src/lib/tic_tac_toe.cpp src/lib/tic_tac_toe.h src/lib/player.cpp src/lib/player.h src/lib/human.cpp src/lib/human.h src/lib/ai.cpp src/lib/ai.h src/exceptions/player/player_exceptions.h)