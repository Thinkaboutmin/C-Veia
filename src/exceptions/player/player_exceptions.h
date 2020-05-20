#ifndef TICTACTOE_PLAYER_EXCEPTIONS_H
#define TICTACTOE_PLAYER_EXCEPTIONS_H

#include <stdexcept>

#define UNUSABLE_SYMBOL_MSG "The desired symbol is not available."

namespace tic_tac_toe {
    class UnusableSymbol : std::runtime_error {
    public:
        UnusableSymbol() : std::runtime_error(UNUSABLE_SYMBOL_MSG) {};
    };
}

#endif //TICTACTOE_PLAYER_EXCEPTIONS_H
