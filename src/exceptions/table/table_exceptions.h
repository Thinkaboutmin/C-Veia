#ifndef TICTACTOE_TABLE_EXCEPTIONS_H
#define TICTACTOE_TABLE_EXCEPTIONS_H

#include <stdexcept>

#define UNAVAILABLE_CELL_MSG "The cell doesn't exist as it is out of range."
#define ROW_IS_ZERO_MSG "Row number needs to be bigger than zero."
#define COLUMN_IS_ZERO_MSG "Column number needs to be bigger than zero"

namespace tic_tac_toe {
    class UnavailableCell : std::runtime_error {
    public:
        UnavailableCell() : std::runtime_error(UNAVAILABLE_CELL_MSG) {}
    };

    class RowIsZero : std::runtime_error {
    public:
        RowIsZero() : std::runtime_error(ROW_IS_ZERO_MSG){}
    };

    class ColumnIsZero : std::runtime_error {
    public:
        ColumnIsZero() : std::runtime_error(COLUMN_IS_ZERO_MSG){}
    };
}
#endif //TICTACTOE_TABLE_EXCEPTIONS_H
