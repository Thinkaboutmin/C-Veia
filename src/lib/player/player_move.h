#ifndef TICTACTOE_PLAYER_MOVE_H
#define TICTACTOE_PLAYER_MOVE_H

#include <string>

/*
 * Holds the row, column and the value of the player meaning it's
 * intent to put a value into a PlainTable class or derivatives.
 */
template<typename T>
struct PlayerMove {
    const unsigned short row = 0;
    const unsigned short column = 0;
    const T *value = nullptr;
    bool failure = false;
    std::string msg;
    std::wstring w_msg;

    PlayerMove(const unsigned short row, const unsigned short column, const T &value) :
              row(row), column(column), value(&value) {}

    PlayerMove() = default;

	void operator = (const PlayerMove<T> & move) {
		this->column = move.column;
		this->row = move.row;
		this->value = move.value;
		this->failure = move.failure;
		this->w_msg = move.w_msg;
		this->msg = move.msg;
	}
};


#endif //TICTACTOE_PLAYER_MOVE_H
