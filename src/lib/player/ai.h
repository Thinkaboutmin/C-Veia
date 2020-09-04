#ifndef TICTACTOE_AI_H
#define TICTACTOE_AI_H

#include <random>
#include <chrono>
#include <map>
#include <utility>
#include <functional>

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
            // Prepare random number generation.
            std::mt19937_64 generator(std::chrono::system_clock::now().time_since_epoch().count());
            shortDistributor dist(0, 1);

            if (dist(generator)) {
                return this->hardMove(table);
            }

            return this->easyMove(table);
        }

        // A 100% calculated move. It will observe the table and
        // move to win accordingly.
        PlayerMove<T> hardMove(PlainTable<T> &table) {
            // TODO: Develop an algorithm which plays thoughtfully. In progress
            rowsAndColumns available_cells = Player<T>::getAvailableMoves(table);
            std::map<const T *, rowsAndColumns> players_cells = table.getSymbolsCells();
            rowsAndColumns my_cells = players_cells[&this->getPlayerSymbol()];
            players_cells.erase(&this->getPlayerSymbol());

            const unsigned int total_index = generateTotalIndex(table.getRowsNum());

            // Resize this player cells if it is the first time
            // playing.
            if (my_cells.size() == 0) {
                my_cells.resize(table.getRowsNum());
            }

            for (std::pair<const T *, rowsAndColumns> player_cell : players_cells) {
                // Verify if only a single cell is missing to win.
                
                PlayerMove<T> move = isWinCertainHorizontal(table, my_cells, total_index);

                // If the move is valid it means that the player is almost winning
                // hence we return a move with the local to stop it.
                if (checkMove(move)) {
                    return move;
                }

                move = isWinCertainVertical(table, my_cells, total_index);
                if (checkMove(move)) {
                    return move;
                }

                move = isWinCertainForwardSlash(table, my_cells, total_index);
                if (checkMove(move)) {
                    return move;
                }

                move = isWinCertainBackwardSlash(table, my_cells, total_index);
                if (checkMove(move)) {
                    return move;
                }

                // Verify if the player is almost winning and plays accordingly if noticed its near win.
                move = this->cancelWinHorizontal(table, player_cell, my_cells, total_index);

                if (checkMove(move)) {
                    return move;
                }

                move = this->cancelWinVertical(table, player_cell, my_cells, total_index);

                if (checkMove(move)) {
                    return move;
                }

                move = this->cancelWinForwardSlash(table, player_cell, my_cells, total_index);

                if (checkMove(move)) {
                    return move;
                }

                move = this->cancelWinBackwardSlash(table, player_cell, my_cells, total_index);

                if (checkMove(move)) {
                    return move;
                }
            }
            
            // TODO: Get the best move.
            return this->easyMove(table);
        }

        /*
         * Check if there's only a single move to guarantee a win.
         *
         * This checks only the horizontal cells.
         *
         * table -> The table of the game.
         * my_cells -> This class pieces, the same as the player cell
         * total_index -> The sum of a horizontal or vertical cells position. It's used to
         * get a cell whenever we have only one missing cell. 
         * 
         * Example: 3x3 table have the following position
         * 
         * Getting the total Index from a row of the table | 1 | 2 | 3 | 
         * hence the total index is 1 + 2 + 3. If we have the postion 
         * 1 and 3 we just have to add 1 + 3 and subtract from total_index
         * to get 2.
         */
        PlayerMove<T> isWinCertainHorizontal(PlainTable<T> & table, const rowsAndColumns & my_cells, const unsigned int & total_index) {
            const unsigned short & rows = table.getRowsNum();
            const unsigned short & column = table.getColumnsNum();

            for (unsigned short row = 1; row <= rows; ++row) {
                const std::vector<unsigned short> & row_v = my_cells[row - 1];
                if (row_v.size() == rows - 1) {
                    unsigned int filled = 0;
                    for (unsigned short column_postion : row_v ) {
                        filled += column_postion;
                    }

                    unsigned short column = total_index - filled;

                    return PlayerMove<T>(row, column, this->getPlayerSymbol());
                }
            }

            return PlayerMove<T>(0, 0, this->getPlayerSymbol());
        }

        /*
         * Check if there's only a single move to guarantee a win.
         *
         * This checks only the vertical cells.
         *
         * table -> The table of the game.
         * my_cells -> This class pieces, the same as the player cell
         * total_index -> The sum of a horizontal or vertical cells position. It's used to
         * get a cell whenever we have only one missing cell. 
         * 
         * Example: 3x3 table have the following position
         * 
         * Getting the total Index from a row of the table | 1 | 2 | 3 | 
         * hence the total index is 1 + 2 + 3. If we have the postion 
         * 1 and 3 we just have to add 1 + 3 and subtract from total_index
         * to get 2.
         */
        PlayerMove<T> isWinCertainVertical(PlainTable<T> & table, const rowsAndColumns & my_cells, const unsigned int & total_index) {
            const unsigned short & rows = table.getRowsNum();
            const unsigned short & columns = table.getColumnsNum();

            for (unsigned short column = 1; column <= columns; ++column) {
                unsigned short matches = 0;
                unsigned int filled = 0;
                for (unsigned short row = 1; row <= rows; ++row) {
                    for (unsigned short column_position : my_cells[row - 1]) {
                        if (column_position == column)  {
                            ++matches;
                            filled += row;
                        }
                    }
                }

                if (matches == columns - 1) {
                    const unsigned short row = total_index - filled;
                    return PlayerMove<T>(row, column, this->getPlayerSymbol());
                }
            }

            return PlayerMove<T>(0, 0, this->getPlayerSymbol());
        }

        /*
         * Check if there's only a single move to guarantee a win.
         *
         * This checks only the forward slash cells.
         *
         * table -> The table of the game.
         * my_cells -> This class pieces, the same as the player cell
         * total_index -> The sum of a horizontal or vertical cells position. It's used to
         * get a cell whenever we have only one missing cell. 
         * 
         * Example: 3x3 table have the following position
         * 
         * Getting the total Index from a row of the table | 1 | 2 | 3 | 
         * hence the total index is 1 + 2 + 3. If we have the postion 
         * 1 and 3 we just have to add 1 + 3 and subtract from total_index
         * to get 2.
         */
        PlayerMove<T> isWinCertainForwardSlash(PlainTable<T> & table, const rowsAndColumns & my_cells, const unsigned int & total_index) {
            const unsigned short & rows = table.getRowsNum();
            const unsigned short & columns = table.getColumnsNum();

            for (unsigned short column = columns, row = 1; row <= rows; ++row, --column) {
                unsigned short matches = 0;
                unsigned int filled_row = 0;
                unsigned int filled_column = 0;
                for (unsigned short column_position : my_cells[row - 1]) {
                    if (column_position == column) {
                        ++matches;
                        filled_row += row;
                        filled_column += column;
                    }
                }

                if (matches == rows) {
                    unsigned short row = total_index - filled_row;
                    // Overshadow the column variable, don't be confused with the other one
                    unsigned short column = total_index - filled_column;

                    return PlayerMove<T>(row, column, this->getPlayerSymbol());
                }
            }

            return PlayerMove<T>(0, 0, this->getPlayerSymbol());
        }

        /*
         * Check if there's only a single move to guarantee a win.
         *
         * This checks only the backwards slash cells.
         *
         * table -> The table of the game.
         * my_cells -> This class pieces, the same as the player cell
         * total_index -> The sum of a horizontal or vertical cells position. It's used to
         * get a cell whenever we have only one missing cell. 
         * 
         * Example: 3x3 table have the following position
         * 
         * Getting the total Index from a row of the table | 1 | 2 | 3 | 
         * hence the total index is 1 + 2 + 3. If we have the postion 
         * 1 and 3 we just have to add 1 + 3 and subtract from total_index
         * to get 2.
         */
        PlayerMove<T> isWinCertainBackwardSlash(PlainTable<T> & table, const rowsAndColumns & my_cells, const unsigned int & total_index) {
            const unsigned short & rows = table.getRowsNum();
            const unsigned short & columns = table.getColumnsNum();

            for (unsigned short column = 1; column <= rows; ++column) {
                unsigned short matches = 0;
                unsigned int filled = 0;
                for (unsigned short column_position : my_cells[column - 1]) {
                    if (column_position == column) {
                        ++matches;
                        filled += column;
                    }
                }

                if (matches == rows) {
                    unsigned short row_column = total_index - filled;

                    return PlayerMove<T>(row_column, row_column, this->getPlayerSymbol());
                }
            }

            return PlayerMove<T>(0, 0, this->getPlayerSymbol());
        }

        /*
         * Check if a player is winning in a horizontal line.
         * If it's not winning we return a PlayerMove<T> without any
         * column and row. Otherwise a fullfiled PlayerMove<T> is given.
         * 
         * table -> The table of the game.
         * player_cell -> It contains it's symbol and the position of such on the table.
         * my_cells -> This class pieces, the same as the player cell
         * total_index -> The sum of a horizontal or vertical cells position. It's used to
         * get a cell whenever we have only one missing cell. 
         * 
         * Example: 3x3 table have the following position
         * 
         * Getting the total Index from a row of the table | 1 | 2 | 3 | 
         * hence the total index is 1 + 2 + 3. If we have the postion 
         * 1 and 3 we just have to add 1 + 3 and subtract from total_index
         * to get 2.
         */
        PlayerMove<T> cancelWinHorizontal(PlainTable<T> & table, const std::pair<const T *, rowsAndColumns> & player_cell, 
                                          const rowsAndColumns & my_cells, const unsigned int & total_index) {
            const unsigned short & rows = table.getRowsNum();
            const unsigned short & columns = table.getColumnsNum();

            for (unsigned short row = 1; row <= rows; ++row) {
                if (player_cell.second[row-1].size() == rows - 1 && my_cells[row -1].size() == 0) {
                    unsigned int filled = 0;
                    
                    for (const unsigned short column_position : player_cell.second[row - 1]) {
                        filled += column_position;
                    }
                    const unsigned short column = total_index - filled;
                    return PlayerMove<T>(row, column, this->getPlayerSymbol());
                }
            }

            // Return an impossible move meaning that there's no win to cancel.
            return PlayerMove<T>(0, 0, this->getPlayerSymbol());
        }   

        /*
         * Check if a player is winning in a vertical line.
         * If it's not winning we return a PlayerMove<T> without any
         * column and row. Otherwise a fullfiled PlayerMove<T> is given.
         * 
         * table -> The table of the game.
         * player_cell -> It contains it's symbol and the position of such on the table.
         * my_cells -> This class pieces, the same as the player cell
         * total_index -> The sum of a horizontal or vertical cells position. It's used to
         * get a cell whenever we have only one missing cell. 
         * 
         * Example: 3x3 table have the following position
         * 
         * Getting the total Index from a row of the table | 1 | 2 | 3 | 
         * hence the total index is 1 + 2 + 3. If we have the postion 
         * 1 and 3 we just have to add 1 + 3 and subtract from total_index
         * to get 2.
         */
        PlayerMove<T> cancelWinVertical(PlainTable<T> & table, const std::pair<const T *, rowsAndColumns> & player_cell, 
                                        const rowsAndColumns & my_cells, const unsigned int & total_index) {
            const unsigned short & rows = table.getRowsNum();
            const unsigned short & columns = table.getColumnsNum();

            // Vertical check.
            std::vector<std::vector<unsigned short>> player_columns;
            std::vector<std::vector<unsigned short>> my_columns;
            player_columns.resize(columns);
            my_columns.resize(columns);

            // Fill the columns
            for (unsigned short row = 1; row <= rows; ++row) {
                if (player_cell.second[row - 1].size() != 0) {
                    for (unsigned short column = 1; column <= columns; ++column) {
                        for (const unsigned short column_verifier : player_cell.second[row - 1]) {
                            if (column_verifier == column) {
                                player_columns[column - 1].emplace_back(row);
                            }
                        }
                    }
                }
                if (my_cells[row - 1].size() != 0) {
                    for (unsigned short column = 1; column <= columns; ++column) {
                        for (const unsigned short column_verifier : my_cells[row - 1]) {
                            if (column_verifier == column) {
                                my_columns[column - 1].emplace_back(row);
                            }
                        }
                    }
                }
            }

            for (unsigned short column = 1; column <= columns; ++column) {
                const std::vector<unsigned short> & player_column = player_columns[column - 1];
                if (player_column.size() == columns - 1 && my_columns[column - 1].size() == 0) {
                    unsigned int filled = 0;
                    for (const unsigned short row_position : player_column) {
                        filled += row_position;
                    }
                    const unsigned short row = total_index - filled;
                    return PlayerMove<T>(row, column, this->getPlayerSymbol());
                }
            }

            // Return an impossible move meaning that there's no win to cancel.
            return PlayerMove<T>(0, 0, this->getPlayerSymbol());
        }

        /*
         * Check if a player is winning in a vertical line.
         * If it's not winning we return a PlayerMove<T> without any
         * column and row. Otherwise a fullfiled PlayerMove<T> is given.
         * 
         * table -> The table of the game.
         * player_cell -> It contains it's symbol and the position of such on the table.
         * my_cells -> This class pieces, the same as the player cell
         * total_index -> The sum of a horizontal or vertical cells position. It's used to
         * get a cell whenever we have only one missing cell. 
         * 
         * Example: 3x3 table have the following position
         * 
         * Getting the total Index from a row of the table | 1 | 2 | 3 | 
         * hence the total index is 1 + 2 + 3. If we have the postion 
         * 1 and 3 we just have to add 1 + 3 and subtract from total_index
         * to get 2.
         */
        PlayerMove<T> cancelWinForwardSlash(PlainTable<T> & table, const std::pair<const T *, rowsAndColumns> & player_cell, 
                                            const rowsAndColumns & my_cells, const unsigned int & total_index) {
            const unsigned short & rows = table.getRowsNum();
            const unsigned short & columns = table.getColumnsNum();

            // Pair representation: row, column
            using row_column = std::pair<unsigned short, unsigned short>;
            std::vector<row_column> player_forward_slash;
            std::vector<row_column> my_forward_slash;

            // Fill our forward slash vector with the actual values
            // of the table.
            unsigned short forward_slash_row;
            for (unsigned short column = columns, row = 1; column != 0; --column, ++row) {
                for (const unsigned short column_position : player_cell.second[row - 1]) {
                    if (column_position == column) {
                        player_forward_slash.emplace_back(row, column);
                        break;
                    }
                }

                for (const unsigned short column_position : my_cells[row - 1]) {
                    if (column_position == column) {
                        my_forward_slash.emplace_back(row, column);
                        break;
                    }
                }
            }
            
            if (player_forward_slash.size() == rows - 1 && my_forward_slash.size() == 0) {
                unsigned short partial_row_index = 0;
                unsigned short partial_column_index = 0;
                for (auto player_pair : player_forward_slash) {
                    partial_row_index += player_pair.first;
                    partial_column_index += player_pair.second;
                }
                const unsigned short row = total_index - partial_row_index;
                const unsigned short column = total_index - partial_column_index;
                return PlayerMove<T>(row, column, this->getPlayerSymbol());
            }

            // Return an impossible move meaning that there's no win to cancel.
            return PlayerMove<T>(0, 0, this->getPlayerSymbol());
        }

        /*
         * Check if a player is winning in a vertical line.
         * If it's not winning we return a PlayerMove<T> without any
         * column and row. Otherwise a fullfiled PlayerMove<T> is given.
         * 
         * table -> The table of the game.
         * player_cell -> It contains it's symbol and the position of such on the table.
         * my_cells -> This class pieces, the same as the player cell
         * total_index -> The sum of a horizontal or vertical cells position. It's used to
         * get a cell whenever we have only one missing cell. 
         * 
         * Example: 3x3 table have the following position
         * 
         * Getting the total Index from a row of the table | 1 | 2 | 3 | 
         * hence the total index is 1 + 2 + 3. If we have the postion 
         * 1 and 3 we just have to add 1 + 3 and subtract from total_index
         * to get 2.
         */
        PlayerMove<T> cancelWinBackwardSlash(PlainTable<T> & table, const std::pair<const T *, rowsAndColumns> & player_cell, 
                                             const rowsAndColumns & my_cells, const unsigned int & total_index) {
            const unsigned short & rows = table.getRowsNum();
            const unsigned short & columns = table.getColumnsNum();

            std::vector<unsigned short> player_back_slash;
            std::vector<unsigned short> my_back_slash;

            unsigned short back_slash_row;
            // Column and row will be the same on the backward slash check.
            for (unsigned short column = 1; column <= columns; ++column) {
                for (const unsigned short column_position : player_cell.second[column - 1]) {
                    if (column_position == column) {
                        player_back_slash.emplace_back(column);
                        break;
                    }
                }

                for (const unsigned short column_position : my_cells[column - 1]) {
                    if (column_position == column) {
                        my_back_slash.emplace_back(column);
                        break;
                    }
                }
            }
            
            if (player_back_slash.size() == rows - 1 && my_back_slash.size() == 0) {;
                unsigned short partial_row_column_index = 0;
                for (unsigned short row_position : player_back_slash) {
                    partial_row_column_index += row_position;
                }
                const unsigned short row_column = total_index - partial_row_column_index;
                return PlayerMove<T>(row_column, row_column, this->getPlayerSymbol());
            }

            // Return an impossible move meaning that there's no win to cancel.
            return PlayerMove<T>(0, 0, this->getPlayerSymbol());
        }

        /*
         * Generate a total index value from a given number.
         * 
         * This generates a number which if looped until it becomes 1
         * while doing sums of it's pasts values.
         */
        const unsigned int generateTotalIndex(const unsigned short & row_column_value) const {
            const unsigned int total_index = [&, row_column_value](){
                // This lambda is used only to get the total number
                // of the sum of rows until it is 1.
                unsigned int total_index = 0;
                for (unsigned short row = 1; row <= row_column_value; ++row) {
                    total_index += row;
                }

                return total_index;
            }();
            
            return total_index;
        }

        /*
         * Check if the move is valid.
         *
         * This checks only the if the column and row
         * are not equal to 0, returning true if such is true.
         * otherwise, false is given.
         */
        bool checkMove(PlayerMove<T> move) {
            if (move.column != 0 && move.row != 0) {
                return true;
            }

            return false;
        }
    };
}


#endif //TICTACTOE_AI_H
