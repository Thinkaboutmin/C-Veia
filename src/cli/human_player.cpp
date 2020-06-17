#include "human_player.h"

#include <iostream>
#include <string>
#include <limits>

HumanPlayer::HumanPlayer(std::wstring symbol, Screen & screen) : Player(symbol), screen(screen) {}

PlayerMove<std::wstring> HumanPlayer::getMove(PlainTable<std::wstring> &table) {
    this->screen.print(L"\n\n");

    PlayerMove<std::wstring> player_move;
    do {
        if (player_move.failure) {
			this->screen.setPlace(this->screen.getRow() + 2, 0).clearLine().print(player_move.w_msg);
			// Reset to the last row otherwise it will shift down
			// because enter means a newline.
			this->screen.setPlace(this->screen.getRow() - 3, 0).clearLine();
        }

		this->screen.print(L"Select the place where you want to play by giving row|column: ");
        
        std::wstring move = this->screen.getLine();
		
        player_move = this->parseMove(move);
    } while(player_move.failure);

    return player_move;
}

PlayerMove<std::wstring> HumanPlayer::parseMove(std::wstring string) {
	constexpr size_t not_found = std::numeric_limits<size_t>::max();

	// Check for the pipe divisor.
	size_t sep_found = string.find('|');
	if (sep_found == not_found) {
		PlayerMove<std::wstring> move;
		move.failure = true;
		move.w_msg = L"Couldn't find the pipe (|) to separate from column to cell";
		return move;
	// If the size is the same as the pipe then assume that
	// it's the last character of a string which size is bigger than the pipe
	// hence no value for column. itself or that's missing the 
	// 
	} else if (sep_found == (string.size() - 1)) {
		PlayerMove<std::wstring> move;
		move.failure = true;
		if (string.size() == 1) {
			move.w_msg = L"Missing column and row value";
		} else {
			move.w_msg = L"Missing column value";
		}
		return move;
	// If the location which the pipe is found is on the first place
	// that means there's no row value.
	} else if (sep_found == 0) {
		PlayerMove<std::wstring> move;
		move.failure = true;
		move.w_msg = L"Missing row value";
		return move;
	}

	// Remove any minus sign.
	while (true) {
		size_t minus_found = string.find('-');
		if (minus_found == not_found) {
			break;
		}

		string.erase(minus_found);
	}

	// Safely verify if there's an error when parsing the row and column string.
	int row;
	try {
		std::wstring s_row = string.substr(0, sep_found);
		row = std::stoi(s_row);
	} catch(std::invalid_argument &_) {
		PlayerMove<std::wstring> move;
		move.failure = true;
		move.w_msg = L"Pass a valid value for the row";
		return move;
	}

	int column;
	try {
		std::wstring s_column = string.substr(sep_found + 1);
		column = std::stoi(s_column);
	} catch (std::invalid_argument &_) {
		PlayerMove<std::wstring> move;
		move.failure = true;
		move.w_msg = L"Pass a valid value for the column";
		return move;
	}

	if (row > PlainTable<std::wstring>::max_row_size) {
		PlayerMove<std::wstring> move;
		move.failure = true;
		move.w_msg = L"Size of the row is too big";
		return move;
	} else if(column > PlainTable<std::wstring>::max_column_size) {
		PlayerMove<std::wstring> move;
		move.failure = true;
		move.w_msg = L"Size of the row is too big";
		return move;
	}

	PlayerMove<std::wstring> move(row, column, this->getPlayerSymbol());

	return move;
}
