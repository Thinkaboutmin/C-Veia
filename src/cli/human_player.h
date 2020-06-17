#ifndef TICTACTOE_HUMAN_PLAYER_H
#define TICTACTOE_HUMAN_PLAYER_H

#include "../lib/player/player.h"

#include <string>

#include  "screen.h"

using namespace tic_tac_toe;
/*
 * A human player for the CliTicTacToe.
 */
class HumanPlayer : public Player<std::wstring> {
public:
    Screen & screen;

public:
    HumanPlayer(std::wstring symbol, Screen & screen);

    PlayerMove<std::wstring> getMove(PlainTable<std::wstring> & table) override;

private:
    PlayerMove<std::wstring> parseMove(std::wstring ws_move);

    PlayerMove<std::wstring> checkIfMoveIsValid(PlayerMove<std::wstring> move, PlainTable<std::wstring> &table,
                                                std::vector<std::vector<unsigned short>> & available_moves);
};


#endif //TICTACTOE_HUMAN_PLAYER_H
