#ifndef TICTACTOE_CLI_TIC_TAC_TOE_H
#define TICTACTOE_CLI_TIC_TAC_TOE_H

#include "../lib/tic_tac_toe/tic_tac_toe.h"
#include "string_table.h"

#include <string>
#include <vector>

using namespace tic_tac_toe;
class CliTicTacToe : public TicTacToe<std::wstring>{
private:
    StringTable * cli_table = nullptr;
public:
    CliTicTacToe(std::vector<Player<std::wstring> *> players, StringTable * table) :
                cli_table(table),
                TicTacToe<std::wstring>(players, table) {}

    /*
     * Prints the string table.
     */
    void showBoard();
};


#endif //TICTACTOE_CLI_TIC_TAC_TOE_H
