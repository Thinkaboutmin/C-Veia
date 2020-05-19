//
// Created by jomar on 19/05/2020.
//

#ifndef TICTACTOE_PLAYER_H
#define TICTACTOE_PLAYER_H
#include <limits>

namespace tic_tac_toe {
    /*
     * Players of the tic tac toe game.
     *
     * The symbol can be controlled manually or automatically (recommended).
     */
    class Player {
    private:
        // Keep in check which symbols are available.
        // TODO: Exchange this variable with a vector of wstring.
        static unsigned char available_symbols;
        unsigned char player_symbol;

    public:
       // Return the player symbol.
       unsigned char getPlayerSymbol();

       Player();

       ~Player();

       Player(const unsigned char symbol);

    private:
        // Pick a symbol accordingly to what is available on available_symbols.
        unsigned char pickSymbol();

        // Verify if the symbol is available and if so returns it.
        unsigned char updateAvailableSymbol(const unsigned char lastSymbol);

        // Tries to free the symbol value.
        void freeSymbol();
    };

}


#endif //TICTACTOE_PLAYER_H
