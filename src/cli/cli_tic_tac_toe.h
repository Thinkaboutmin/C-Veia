#ifndef TICTACTOE_CLI_TIC_TAC_TOE_H
#define TICTACTOE_CLI_TIC_TAC_TOE_H

#include "../lib/tic_tac_toe/tic_tac_toe.h"
#include "string_table.h"

#include <string>
#include <vector>

using namespace tic_tac_toe;
class CliTicTacToe : TicTacToe<std::wstring>{
private:
    StringTable &refTable;
public:
    CliTicTacToe(std::vector<Player<std::wstring>> players, StringTable table) :
                TicTacToe(players, table),
                refTable(static_cast<StringTable>(this->table)){}

    /*
     * Prints the string table.
     */
    void showBoard();
};


#endif //TICTACTOE_CLI_TIC_TAC_TOE_H
