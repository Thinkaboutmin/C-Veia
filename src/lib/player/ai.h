#ifndef TICTACTOE_AI_H
#define TICTACTOE_AI_H

#include "player.h"
#include "../../exceptions/player/player_exceptions.h"
#include "players_enum.h"

namespace tic_tac_toe {
    template<typename T>
    class AI : Player<T> {
    private:
        difficulty type;

    public:
        explicit AI(T symbol, difficulty dif = difficulty::DEFAULT);

        void setDifficulty(difficulty dif);

        const difficulty& getDifficulty();

        PlayerMove<T> getMove(const PlainTable<T> &table) override;


    private:
        static bool difficultyIsValid(difficulty dif);

        // Does not care about the table state. It will be
        // consistently of random moves.
        PlayerMove<T> easyMove(const PlainTable<T> &table);

        // There's a 50% chance of it being random or calculated.
        // Basically a mixture of easyMove and hardMove.
        PlayerMove<T> normalMove(const PlainTable<T> &table);

        // A 100% calculated move. It will observe the table and
        // move to win accordingly.
        PlayerMove<T> hardMove(const PlainTable<T> &table);
    };
}


#endif //TICTACTOE_AI_H
