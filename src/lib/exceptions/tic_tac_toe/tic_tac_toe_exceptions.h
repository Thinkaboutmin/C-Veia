#ifndef TICTACTOE_TIC_TAC_TOE_EXCEPTIONS_H
#define TICTACTOE_TIC_TAC_TOE_EXCEPTIONS_H

#include <stdexcept>

#define NOT_ENOUGH_PLAYERS_MSG "It's necessary to have at least one player on the game."
#define TABLE_IS_NOT_EQUAL_IN_SIDES_MSG "The number os rows and columns need to be equal."
#define EMPTY_VALUE_CONFLICT_MSG "The empty value is conflicting with some player symbol."

class NotEnoughPlayers : public std::runtime_error {
public:
    NotEnoughPlayers() : std::runtime_error(NOT_ENOUGH_PLAYERS_MSG){}
};


class TableIsNotEqualInSides : public std::runtime_error {
public:
    TableIsNotEqualInSides() : std::runtime_error(TABLE_IS_NOT_EQUAL_IN_SIDES_MSG){}
};

class EmptyValueConflict : public std::runtime_error {
public:
    EmptyValueConflict() : std::runtime_error(EMPTY_VALUE_CONFLICT_MSG){}
};

#endif //TICTACTOE_TIC_TAC_TOE_EXCEPTIONS_H
