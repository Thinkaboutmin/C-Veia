#include <iostream>
#include <string>
#include <limits>

#include "human_player.h"

HumanPlayer::HumanPlayer(std::wstring symbol, std::wiostream & stream) : Player(symbol), stream(stream) {}

PlayerMove<std::wstring> HumanPlayer::getMove(PlainTable<std::wstring> &table) {
    unsigned int col_write = table.getRowsNum();
    this->stream << L"\n\n";
    col_write += 2;

    PlayerMove<std::wstring> player_move;
    do {
        if (player_move.failure) {
            this->stream << L"\n" << player_move.w_msg;
        }

        this->stream << L"Select the place where you want to play by giving row|column: ";
        std::wstring move;
        std::getline(this->stream, move);
        //player_move = this->parseMove(move); TODO

    } while(player_move.failure);

    return player_move;
}