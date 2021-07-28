#ifndef AI_MIN_MAX_H
#define AI_MIN_MAX_H

#include <vector>
#include "player.h"
#include "../tic_tac_toe/tic_tac_toe.h"


namespace tic_tac_toe {
    template<typename T>
    class AIMinMax : public Player<T> {
    private:
        std::vector<int> tableValues;
        TicTacToe<T> * gameJudge = nullptr;

    public:
        AIMinMax(T symbol) : Player<T>(symbol) {}

        PlayerMove<T> getMove(PlainTable<T> &table) override {
            auto players = this->gameJudge->getPlayers();
            int position = 0;
            for (; position < players.size(); ++position) {
                if (players[position] == this) {
                    break;
                }
            }

            int depth = 0;
            auto cells = table.getEmptyCells();
            for (const auto cell : cells) {
                depth += cell.size();
            }

            auto move = minMaxMoves(table, depth, position);

            return move.first;
        }

        void injectJudge(TicTacToe<T> * gameJudge) {
            this->gameJudge = gameJudge;
        }


    private:
        std::pair<PlayerMove<T>, short> minMaxMoves(PlainTable<T> &table, int depth, int playerIndex) {
            this->gameJudge->getNextPlayer();
            auto status = this->gameJudge->isThereAWinner();
            const Player<T> * player = this->gameJudge->getPlayers()[playerIndex];

            if (status != GameStatus::ONGOING || depth == 0) {
                switch(status) {
                    case GameStatus::DRAW:
                        return std::make_pair(PlayerMove<T>(), 0);
                    case GameStatus::WIN:
                        if (this->gameJudge->getWinner() == this) {
                            return std::make_pair(PlayerMove<T>(), 1);
                        } else {
                            return std::make_pair(PlayerMove<T>(), -1);
                        }
                }
            }

            // Get the empty cells of our game
            std::vector<std::vector<unsigned short>> cells = table.getEmptyCells();

            std::pair<PlayerMove<T>, short> best;
            if (player == this) {
                best = std::make_pair(PlayerMove<T>(), std::numeric_limits<short>::min());
            } else {
                best = std::make_pair(PlayerMove<T>(), std::numeric_limits<short>::max());
            }
            

            // Row
            for(unsigned short i = 1; i <= cells.size(); ++i) {
                // Column
                for (const unsigned short & j : cells[i - 1]) {
                    table.setCellValue(i, j, &player->getPlayerSymbol());

                    auto newMove = this->minMaxMoves(table, depth - 1, this->getNextPlayer(playerIndex));
                    newMove.first = PlayerMove<T>(i, j, player->getPlayerSymbol());
                    table.setCellValue(i, j, &table.getEmptyValue());
                    
                    // Max
                    if (player == this) {
                        if (newMove.second > best.second) {
                            best = newMove;
                        }
                    } else {
                        if (newMove.second < best.second) {
                            best = newMove;
                        }
                    }
                }
            }

            return best;
        }

        int getNextPlayer(int aPosition) {
            if (aPosition + 1 == this->gameJudge->getPlayers().size()) {
                return 0;
            }

            return aPosition + 1;
        }
    };
}


#endif // AI_MIN_MAX_H