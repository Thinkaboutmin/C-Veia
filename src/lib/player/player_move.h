#ifndef TICTACTOE_PLAYER_MOVE_H
#define TICTACTOE_PLAYER_MOVE_H

/*
 * Holds the row, column and the value of the player meaning it's
 * intent to put a value into a PlainTable class or derivatives.
 */
template<typename T>
struct PlayerMove {
    const unsigned short row;
    const unsigned short column;
    const T & value;

    PlayerMove(const unsigned short row, const unsigned short column, const T &value) :
              row(row), column(column), value(value) {}
};


#endif //TICTACTOE_PLAYER_MOVE_H
