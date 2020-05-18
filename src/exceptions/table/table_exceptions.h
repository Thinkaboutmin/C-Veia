#ifndef TICTACTOE_TABLE_EXCEPTIONS_H
#define TICTACTOE_TABLE_EXCEPTIONS_H

#include <stdexcept>

#define UNAVAILABLE_CELL_MSG "The cell doesn't exist as it is out of range."

class UnavailableCell : std::runtime_error {
public:
    UnavailableCell() : std::runtime_error(UNAVAILABLE_CELL_MSG) {}
};

#endif //TICTACTOE_TABLE_EXCEPTIONS_H
