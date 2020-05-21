//
// Created by jomar on 19/05/2020.
//

#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H

#include <limits>
#include <list>
#include <string>

#include "../table/plain_table.hpp"
#include "player_move.h"

namespace tic_tac_toe {
    /*
     * Players of the tic tac toe game.
     *
     * Symbols for each player should be different from others players
     * otherwise an UnusableSymbol exception will be thrown.
     *
     * The symbol is freed after the Player deleter is called.
     */
    template<typename T>
    class Player {
    private:
        static std::list<T> players_symbols;
        T player_symbol;

    public:
       // Return the player symbol.
       const T& getPlayerSymbol();

       ~Player();

       explicit Player(const T& symbol);

       // Make the player act by getting its move intent.
       virtual PlayerMove<T> getMove(PlainTable<T> table) = 0;

    protected:
        // Verify in our list of player symbols if there's match. If so,
        // returns true otherwise false.
        static bool verifyIfUsedSymbol(const T& symbol);
    };
}


#endif //TICTACTOE_PLAYER_H
