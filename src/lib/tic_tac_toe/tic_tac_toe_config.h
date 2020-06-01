//
// Created by jomar on 29/05/2020.
//

#ifndef TICTACTOE_TIC_TAC_TOE_CONFIG_H
#define TICTACTOE_TIC_TAC_TOE_CONFIG_H

#include <vector>

namespace tic_tac_toe {
    template<typename T>
    /*
     * Configure the game according to your rules.
     *
     * player_symbols -> Number of players and their respective symbols. Order matter for
     * who is going to play first. Needs to be configured.
     * columns -> Number of columns on the table. Default is 3
     * rows -> Number of rows on the table. Default is 3
     * empty_value -> Define the empty value for our table.
     */
    struct TicTacToeConfig {
        // Define number of players and their symbols.
        std::vector<T> player_symbols;

        // Define the size of our table.
        unsigned short columns = 3;
        unsigned short rows = 3;

        // Define the empty value for the table.
        T empty_value = T();

        TicTacToeConfig(std::vector<T> player_symbols, T empty_value = T(),
                        unsigned short columns = 3, unsigned rows = 3) :
                        columns(columns), rows(rows),
                        player_symbols(player_symbols), empty_value(empty_value) {}
    };
}


#endif //TICTACTOE_TIC_TAC_TOE_CONFIG_H
