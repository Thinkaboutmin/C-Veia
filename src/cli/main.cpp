#include <string>

#include "cli_tic_tac_toe.h"
#include "../lib/player/ai.h"
#include "string_table.h"
#include "utils.h"
#include <iostream>

using namespace tic_tac_toe;
int main(int argc, char ** argv) {
    //AI<std::wstring> player_1{L"X"};
    //AI<std::wstring> player_2{L"O"};
    //StringTable table{3, 3};
    //CliTicTacToe game({player_1, player_2}, table);

    /*
    do {
        clearScreen();
        setPlace(1, 1);
        game.showBoard();
        setPlace(table.getRowsNum() + 2, 1);
        std::cout << "Make a move: "
    } while(!game.isThereAWinner());

    std::cout << "Player " << *game.getWinner() << " won!";*/

    return 0
}
