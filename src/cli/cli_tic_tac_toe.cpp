#include "cli_tic_tac_toe.h"
#include <iostream>

void CliTicTacToe::showBoard() {
    std::wcout << this->cli_table->tableString();
}