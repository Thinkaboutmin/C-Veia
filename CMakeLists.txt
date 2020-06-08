cmake_minimum_required(VERSION 3.17)
project(ticTacToe)

set(CMAKE_CXX_STANDARD 20)

# Choose which binary to compile.

# Defaults to cli compilation even if it's off.
option(CLI_COMPILE "Compile the cli version of the tic tac toe game." OFF)
# Not implemented yet! TODO
option(OPENGL_COMPILE "Compile the opengl version of the tic tac toe game." OFF)
# Not implemented yet TODO
option(VULKAN_COMPILE "Compile the vulkan version of the tic tac toe game" OFF)

set(TIC_TAC_TOE_LIB src/lib/table/plain_table.h src/cli/string_table.h
        src/cli/string_table.cpp src/lib/exceptions/table/table_exceptions.h
        src/lib/tic_tac_toe/tic_tac_toe.h src/lib/player/player.h src/lib/player/ai.cpp
        src/lib/player/ai.h src/lib/exceptions/player/player_exceptions.h
        src/lib/player/player_move.h src/lib/player/players_enum.h
        src/lib/exceptions/tic_tac_toe/tic_tac_toe_exceptions.h)

if (CLI_COMPILE)
    file(GLOB SOURCES src/cli/*.cpp src/cli/*.h)
elseif(OPENGL_COMPILE)
    file(GLOB SOURCES src/opengl/*.cpp src/opengl/*.h)
elseif(VULKAN_COMPILE)
    file(GLOB SOURCES src/vulkan/*.cpp src/vulkan/*.h)
else()
    file(GLOB SOURCES src/cli/*.cpp src/cli/*.h)
endif()

add_executable(ticTacToe ${SOURCES} ${TIC_TAC_TOE_LIB})
