#ifndef TICTACTOE_HUMAN_H
#define TICTACTOE_HUMAN_H

#include "player.h"

namespace tic_tac_toe {
    template<typename T>
    class Human : Player<T> {
    public:
        PlayerMove<T> getMove(PlainTable<T> table) override;
    };
}

#endif //TICTACTOE_HUMAN_H
