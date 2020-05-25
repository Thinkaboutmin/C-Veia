cmake_minimum_required(VERSION 3.17)
project(ticTacToe)

set(CMAKE_CXX_STANDARD 20)
add_executable(ticTacToe src/lib/table/plain_table.h src/cli/string_table.h src/cli/string_table.cpp src/exceptions/table/table_exceptions.h src/lib/tic_tac_toe/tic_tac_toe.h src/lib/player/player.h src/lib/player/ai.cpp src/lib/player/ai.h src/exceptions/player/player_exceptions.h src/lib/player/player_move.h src/lib/player/players_enum.h src/exceptions/tic_tac_toe/tic_tac_toe_exceptions.h)
