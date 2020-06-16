#include "cli_tic_tac_toe.h"

#include <iostream>

CliTicTacToe & CliTicTacToe::showBoard() {
    this->screen.print(this->cli_table->tableString());

    return *this;
}
