#ifndef TICTACTOE_PLAYER_MOVE_H
#define TICTACTOE_PLAYER_MOVE_H

#include <string>

/*
 * Holds the row, column and the value of the player meaning it's
 * intent to put a value into a PlainTable class or derivatives.
 */
template<typename T>
struct PlayerMove {
    private:
        unsigned short b_row = 0;
        unsigned short b_column = 0;
    public:
        const unsigned short &row = b_row;
        const unsigned short &column = b_column;
        const T *value = nullptr;
        bool failure = false;
        std::string msg;
        std::wstring w_msg;

    PlayerMove(const unsigned short row, const unsigned short column, const T &value) :
              b_row(row), b_column(column), value(&value) {}

    PlayerMove() = default;

	void operator = (PlayerMove<T> move) {
		this->b_column = move.column;
		this->b_row = move.row;
		this->value = move.value;
		this->failure = move.failure;
		this->w_msg = move.w_msg;
		this->msg = move.msg;
	}
};


#endif //TICTACTOE_PLAYER_MOVE_H
