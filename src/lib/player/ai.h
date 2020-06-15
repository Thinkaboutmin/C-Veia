#ifndef TICTACTOE_AI_H
#define TICTACTOE_AI_H

#include <random>
#include <chrono>

#include "player.h"
#include "../exceptions/player/player_exceptions.h"
#include "player_move.h"
#include "players_enum.h"

namespace tic_tac_toe {
    template<typename T>
    class AI : public Player<T> {

    /**************************************************************
     *                     Variable Definition                    *
     **************************************************************/
    private:
        difficulty type;

    /**************************************************************
     *                     Variable Definition                    *
     **************************************************************/
    public:
        AI(T symbol, difficulty dif = difficulty::DEFAULT) : Player<T>(symbol) {
           setDifficulty(dif);
        }

        /*
         * Set the difficulty which the AI will be playing as.
         *
         * If the difficulty is invalid an error will be thrown.
         */
        AI & setDifficulty(difficulty dif) {
            if (difficultyIsValid(dif)) {
                this->type = dif;
            } else {
                throw UnknownDifficulty();
            }

            return *this;
        }

        const difficulty& getDifficulty() {
            return this->type;
        }

        PlayerMove<T> getMove(PlainTable<T> &table) override {
            switch (this->type) {
                case difficulty::DEFAULT:
                case difficulty::NORMAL:
                    return this->normalMove(table);
                case difficulty::EASY:
                    return this->easyMove(table);
                case difficulty::HARD:
                    return this->hardMove(table);
                default:
                    // Throwing an error here seems misleading and breaks
                    // the design of the application for now it will be kept.
                    throw UnknownDifficulty();
            }
        }

    private:
        static bool difficultyIsValid(difficulty dif) {
            switch (dif) {
                case difficulty::DEFAULT:
                case difficulty::EASY:
                case difficulty::NORMAL:
                case difficulty::HARD:
                    return true;
                default:
                    return false;
            }
        }

        using shortDistributor = std::uniform_int_distribution<unsigned short>;
        // Does not care about the table state. It will be
        // consistently of random moves.
        PlayerMove<T> easyMove(PlainTable<T> &table) {
            rowsAndColumns available_cells = Player<T>::getAvailableMoves(table);
            // As we erase cells we will need to have a ordered list
            // which holds data about the available rows index.
            std::vector<unsigned short> available_rows;
            for (unsigned short index_row = 0; index_row < table.getRowsNum(); ++index_row) {
                available_rows.emplace_back(index_row);
            }

            // Prepare random number generation.
            std::mt19937_64 generator(std::chrono::system_clock::now().time_since_epoch().count());
            shortDistributor dist(0,  available_rows.size() - 1);

            while(available_rows.size() != 0) {
                unsigned short row = dist(generator); // Pseudo row index from ordered list
                unsigned short true_row = available_rows[row]; // Actual row index

                unsigned short columns = available_cells[true_row].size();
                if (columns == 0) {
                    available_rows.erase(available_rows.begin() + row);
                    // Redefine possible values for ordered list.
                    dist.param(shortDistributor::param_type(0, available_rows.size() - 1));
                    continue;
                } else if (columns == 1) {
                    // Disregard any cpu cycle here, just send the last column
                    // and be done with it.
                    return PlayerMove<T>(true_row + 1, available_cells[true_row][0], this->getPlayerSymbol());
                }

                dist.param(shortDistributor::param_type(0, columns - 1));
                unsigned short column = dist(generator);

                return PlayerMove<T>(true_row + 1, available_cells[true_row][column], this->getPlayerSymbol());
            }

            throw OutOfMove();
        }

        // There's a 50% chance of it being random or calculated.
        // Basically a mixture of easyMove and hardMove.
        PlayerMove<T> normalMove(PlainTable<T> &table) {
            // TODO: After hard mode, make the fifty-fifty.
            return this->easyMove(table);
        }

        // A 100% calculated move. It will observe the table and
        // move to win accordingly.
        PlayerMove<T> hardMove(PlainTable<T> &table) {
            // TODO: Develop an algorithm which plays thoughtfully.
            // rowsAndColumns available_cells = Player<T>::getAvailableMoves();

            return PlayerMove<T>(0, 0, T());
        }
    };
}


#endif //TICTACTOE_AI_H
