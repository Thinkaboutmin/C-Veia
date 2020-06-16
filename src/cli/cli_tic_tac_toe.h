#ifndef TICTACTOE_CLI_TIC_TAC_TOE_H
#define TICTACTOE_CLI_TIC_TAC_TOE_H

#include "../lib/tic_tac_toe/tic_tac_toe.h"

#include <string>
#include <vector>
#include <iostream>

#include "string_table.h"
#include "screen.h"

using namespace tic_tac_toe;

/*
 * Cli tic tac toe game.
 */
class CliTicTacToe : public TicTacToe<std::wstring>{
private:
    StringTable * cli_table = nullptr;
	Screen &screen;
public:
    CliTicTacToe(Screen & screen, std::vector<Player<std::wstring> *> players, StringTable * table) :
                cli_table(table), screen(screen),
                TicTacToe<std::wstring>(players, table) {}

    /*
     * Prints the string table.
     */
    CliTicTacToe & showBoard();
};


#endif //TICTACTOE_CLI_TIC_TAC_TOE_H
