#ifndef TICTACTOE_TIC_TAC_TOE_EXCEPTIONS_H
#define TICTACTOE_TIC_TAC_TOE_EXCEPTIONS_H

#include <stdexcept>

#define NOT_ENOUGH_PLAYERS_MSG "It's necessary to have at least one player on the game."
#define TABLE_IS_NOT_EQUAL_IN_SIDES_MSG "The number os rows and columns need to be equal."

class NotEnoughPlayers : std::runtime_error {
public:
    NotEnoughPlayers() : std::runtime_error(NOT_ENOUGH_PLAYERS_MSG){}
};


class TableIsNotEqualInSides : std::runtime_error {
public:
    TableIsNotEqualInSides() : std::runtime_error(TABLE_IS_NOT_EQUAL_IN_SIDES_MSG){}
};

#endif //TICTACTOE_TIC_TAC_TOE_EXCEPTIONS_H
