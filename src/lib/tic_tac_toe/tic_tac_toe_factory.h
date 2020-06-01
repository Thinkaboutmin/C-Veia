//
// Created by jomar on 29/05/2020.
//

#ifndef TICTACTOE_TIC_TAC_TOE_FACTORY_H
#define TICTACTOE_TIC_TAC_TOE_FACTORY_H

#include <vector>

#include "tic_tac_toe.h"
#include "tic_tac_toe_config.h"
#include "../player/player.h"
#include "../table/plain_table.h"

namespace tic_tac_toe {
    template<typename T>
    class TicTacToeFactory {
    public:
        TicTacToe<T> makeGame(const TicTacToeConfig<T> &config) {
            auto players = new std::vector<Player<T>>();
            for (T symbol : config.player_symbols) {
                players->emplace_back(Player<T>(symbol));
            }

            auto table = new PlainTable<T>(config.rows, config.columns, config.empty_value);

            return TicTacToe(players, table);
        }
    };
}


#endif //TICTACTOE_TIC_TAC_TOE_FACTORY_H
