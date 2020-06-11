#ifndef TICTACTOE_TIC_TAC_TOE_ENUM_H
#define TICTACTOE_TIC_TAC_TOE_ENUM_H

namespace tic_tac_toe {

    /*
     * Define the status of the game.
     */
    enum GameStatus {
        ONGOING, // Nobody won and there's still empty cells
        DRAW, // No empty cells available
        WIN // Win... :)
    };
}

#endif //TICTACTOE_TIC_TAC_TOE_ENUM_H
