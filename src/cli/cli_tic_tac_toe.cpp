#include "cli_tic_tac_toe.h"
#include <iostream>

void CliTicTacToe::showBoard() {
    std::cout << (static_cast<StringTable>(this->table)).tableString();
}