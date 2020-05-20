//
// Created by jomar on 19/05/2020.
//

#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H
#include <limits>
#include <list>
#include <string>

namespace tic_tac_toe {
    /*
     * Players of the tic tac toe game.
     *
     * Symbols for each player should be different from others players
     * otherwise an UnusableSymbol exception will be thrown.
     *
     * The symbol is freed after the Player deleter is called.
     */
    class Player {
    private:

        static std::list<std::wstring> players_symbols;
        std::wstring player_symbol;


    public:
       // Return the player symbol.
       std::wstring getPlayerSymbol();

       ~Player();

       explicit Player(const std::wstring& symbol);

    protected:
        // Verify in our list of player symbols if there's match. If so,
        // returns true otherwise false.
        static bool verifyIfUsedSymbol(const std::wstring& symbol);
    };
}


#endif //TICTACTOE_PLAYER_H
