#include "cli_tic_tac_toe.h"

#include <iostream>

CliTicTacToe & CliTicTacToe::showBoard(std::wostream &out) {
    out << this->cli_table->tableString();

    return *this;
}