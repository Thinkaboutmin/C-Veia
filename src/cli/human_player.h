#ifndef TICTACTOE_HUMAN_PLAYER_H
#define TICTACTOE_HUMAN_PLAYER_H

#include "../lib/player/player.h"

#include <string>

using namespace tic_tac_toe;
/*
 * A human player for the CliTicTacToe.
 */
class HumanPlayer : Player<std::wstring> {
public:
    std::wiostream & stream;

public:
    HumanPlayer(std::wstring symbol, std::wiostream & stream);

    PlayerMove<std::wstring> getMove(PlainTable<std::wstring> & table) override;

private:
    PlayerMove<std::wstring> parseMove(std::wstring ws_move);
};


#endif //TICTACTOE_HUMAN_PLAYER_H
