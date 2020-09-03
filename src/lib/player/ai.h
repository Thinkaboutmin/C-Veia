#ifndef TICTACTOE_AI_H
#define TICTACTOE_AI_H

#include <random>
#include <chrono>
#include <map>
#include <utility>

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
            // TODO: Develop an algorithm which plays thoughtfully. In progress
            rowsAndColumns available_cells = Player<T>::getAvailableMoves(table);
            std::map<const T *, rowsAndColumns> players_cells = table.getSymbolsCells();
            rowsAndColumns my_cells = players_cells[&this->getPlayerSymbol()];


            const short & rows = table.getRowsNum();
            const short & columns = table.getColumnsNum();
            for (std::pair<const T *, rowsAndColumns> player_cell : players_cells) {
                const unsigned int total_index = [&, rows](){
                        // This lambda is used only to get the total number
                        // of the sum of rows until it is 1.
                        unsigned int total_index = 0;
                        for (unsigned short row = 1; row <= rows; ++row) {
                            total_index += row;
                        }

                        return total_index;
                    }();
                        
                // Horizontal check
                // Check if a player is almost winning by just one tile.
                for (unsigned short row = 1; row <= rows; ++row) {
                    if (player_cell.second[row-1].size() == rows - 1) {
                        unsigned int filled = 0;
                        
                        for (const unsigned short column_position : player_cell.second[row - 1]) {
                            filled += column_position;
                        }
                        const unsigned short column = total_index - filled;
                        return PlayerMove<T>(row, column, this->getPlayerSymbol());
                    }
                }

                // Vertical check.
                std::vector<std::vector<unsigned short>> player_columns;
                player_columns.resize(columns);

                // Fill the columns
                for (unsigned short row = 1; row <= rows; ++row) {
                    for (unsigned short column = 1; column <= columns; ++column) {
                        player_columns[column - 1].emplace_back(player_cell.second[row - 1][column - 1]);
                    }
                }

                for (unsigned short column = 1; column <= columns; ++column) {
                    const std::vector<unsigned short> & player_column = player_columns[column - 1];
                    if (player_column.size() == columns - 1) {
                        unsigned int filled = 0;
                        
                        for (const unsigned short column_position : player_column) {
                            filled += column_position;
                        }
                        const unsigned short row = total_index - filled;
                        return PlayerMove<T>(row, column, this->getPlayerSymbol());
                    }
                }
                
                // TODO:
                // Forward slash check
                rowsAndColumns player_forward_slash;
                player_forward_slash.resize(rows);
                unsigned short forward_slash_row;
                for (unsigned short column = columns, row = 1; column != 0; --column, ++row) {
                    for (const unsigned short column_position : player_cell.second[row - 1]) {
                        if (column_position == column) {
                            player_forward_slash[row -1].emplace_back(column);
                            break;
                        }
                    }
                }
                
                if (player_forward_slash.size() == rows - 1) {
                    unsigned int filled = 0;
                    unsigned short row = 0;
                    unsigned int counter;
                    for (std::vector<unsigned short> forward_slash_row : player_forward_slash) {
                        ++counter;
                        if (forward_slash_row.size() != 0) {
                            row = counter;
                        } else {
                            filled += forward_slash_row[0];
                        }
                    }
                    unsigned short column = total_index - filled;
                    return PlayerMove<T>(row, column, this->getPlayerSymbol());
                }
                
                // Backward slash check
                rowsAndColumns player_back_slash;
                player_forward_slash.resize(rows);
                unsigned short back_slash_row;
                // Column and row will be the same on the backward slash check.
                for (unsigned short column = 1; column <= columns; ++column) {
                    for (const unsigned short column_position : player_cell.second[column - 1]) {
                        if (column_position == column) {
                            player_forward_slash[column -1].emplace_back(column);
                            break;
                        }
                    }
                }
                
                if (player_back_slash.size() == rows - 1) {;
                    unsigned short row = 0;
                    unsigned int counter;
                    for (std::vector<unsigned short> forward_slash_row : player_forward_slash) {
                        ++counter;
                        if (forward_slash_row.size() != 0) {
                            row = counter;
                        }
                    }
                    return PlayerMove<T>(row, row, this->getPlayerSymbol());
                }
            }
            
            // TODO: Get the best move.
            return this->easyMove(table);
        }
    };
}


#endif //TICTACTOE_AI_H
