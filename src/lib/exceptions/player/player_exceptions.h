#ifndef TICTACTOE_PLAYER_EXCEPTIONS_H
#define TICTACTOE_PLAYER_EXCEPTIONS_H

#include <stdexcept>

#define UNUSABLE_SYMBOL_MSG "The desired symbol is not available."
#define UNUSABLE_SYMBOL_WMSG L"The desired symbol is not available."
#define UNKNOWN_DIFFICULTY_MSG "Given difficulty does not exist."
#define UNKNOWN_DIFFICULTY_WMSG L"Given difficulty does not exist."
#define OUT_OF_MOVE_MSG "There's no move available for the player."
#define OUT_OF_MOVE_WMSG L"There's no move available for the player."

namespace tic_tac_toe {
    class UnusableSymbol : public std::runtime_error {
    public:
        UnusableSymbol() : std::runtime_error(UNUSABLE_SYMBOL_MSG) {};
    };

    class UnknownDifficulty : public std::runtime_error {
    public:
        UnknownDifficulty() : std::runtime_error(UNKNOWN_DIFFICULTY_MSG) {}
    };

    class OutOfMove : public std::runtime_error {
    public:
        OutOfMove() : std::runtime_error(OUT_OF_MOVE_MSG) {}
    };
}

#endif //TICTACTOE_PLAYER_EXCEPTIONS_H
