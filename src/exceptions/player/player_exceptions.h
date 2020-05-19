#ifndef TICTACTOE_PLAYER_EXCEPTIONS_H
#define TICTACTOE_PLAYER_EXCEPTIONS_H

#include <stdexcept>

#define OUT_OF_SYMBOLS_MSG "There's no symbols leftover for use on the player."
#define UNUSABLE_SYMBOL_MSG "The desired symbol is not available."

namespace tic_tac_toe {
    class OutOfSymbols : std::runtime_error {
    public:
        OutOfSymbols() : std::runtime_error(OUT_OF_SYMBOLS_MSG) {};
    };

    class UnusableSymbol : std::runtime_error {
    public:
        UnusableSymbol() : std::runtime_error(UNUSABLE_SYMBOL_MSG) {};
    };
}

#endif //TICTACTOE_PLAYER_EXCEPTIONS_H
