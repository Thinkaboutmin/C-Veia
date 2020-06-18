#ifndef TICTACTOE_TIC_TAC_TOE_H
#define TICTACTOE_TIC_TAC_TOE_H

#include <vector>

#include "../player/player.h"
#include "../table/plain_table.h"
#include "../exceptions/tic_tac_toe/tic_tac_toe_exceptions.h"
#include "tic_tac_toe_enum.h"

namespace tic_tac_toe {
    template<typename T>
    /*
     * Tic Tac Toe game control.
     *
     * Here we get the control for the game to get the next player to play and
     * check the table for a winner. The player move is dependent by the user to
     * implement such the same applies to the winner check condition
     * which needs to be explicit asked.
     */
    class TicTacToe {

    /**************************************************************
     *                     Variable Definition                    *
     **************************************************************/
    protected:
        std::vector<Player<T> *> players;
        unsigned short playerToPlay = 0;
        PlainTable<T> *table = nullptr;
        Player<T> * winner = nullptr;

    /**************************************************************
     *                     Function Definition                    *
     **************************************************************/
    public:
        /*
         * Constructor
         *
         * players -> An ordered list of players. The first there is the first to play.
         * table -> The actual table in which the game should occur.
         */
        TicTacToe(std::vector<Player<T> *> players, PlainTable<T> * table) :
                table(table), players(players) {
            if (this->players.empty()) {
                throw NotEnoughPlayers();
            }

            // Make sure that each player have a different symbol.
            for (Player<T> * player : this->players) {
                if (player->getPlayerSymbol() == table->getEmptyValue()) {
                    throw EmptyValueConflict();
                }
            }

            if (this->table->getRowsNum() != this->table->getColumnsNum()) {
                throw TableIsNotEqualInSides();
            }
        }

        TicTacToe<T> & playerPlay() {
            PlayerMove<T> move = getNextPlayer().getMove(*table);
            table->setCellValue(move.row, move.column, move.value);

            return *this;
        }

        // Return the next player of our vector.
        Player<T> & getNextPlayer() {
            if (playerToPlay > players.size() - 1) {
                playerToPlay = 0;
            }

            Player<T> &player = *(players[playerToPlay]);
            ++playerToPlay;
            return player;
        }

        // Verifies for the given table for a winner.
        GameStatus isThereAWinner() {
            T checkSymbol = table->getEmptyValue();

            bool win = false;
            // Check each column in a row for a horizontal win.
            for (unsigned short row = 1; row <= table->getRowsNum(); ++row) {
                for (unsigned short column = 1; column <= table->getColumnsNum(); ++column) {
                    T symbol = *table->getCellValue(row, column);
                    if (symbol == table->getEmptyValue()) {
                        win = false;
                        break;
                    } else if (checkSymbol == table->getEmptyValue()) {
                        // What if the table is 1x1? Let's make it a win :P
                        win = true;
                        checkSymbol = symbol;
                    } else if (checkSymbol == symbol) {
                        // Keep the win condition true until something goes wrong.
                        win = true;
                    } else {
                        win = false;
                        break;
                    }
                }

                if (!win) {
                    // Renew symbol to empty one
                    checkSymbol = table->getEmptyValue();
                } else {
                    break;
                }
            }

            if (!win) {
                // Check for each row in a column for a vertical win.
                for (unsigned short column = 1; column <= table->getColumnsNum(); ++column) {
                    for (unsigned short row = 1; row <= table->getRowsNum(); ++row) {
                        T symbol = *table->getCellValue(row, column);
                        if (symbol == table->getEmptyValue()) {
                            win = false;
                            break;
                        } else if (checkSymbol == table->getEmptyValue()) {
                            // What if the table is 1x1? Let's make it a win :P
                            win = true;
                            checkSymbol = symbol;
                        } else if (checkSymbol == symbol) {
                            // Keep the win condition true until something goes wrong.
                            win = true;
                        } else {
                            win = false;
                            break;
                        }
                    }

                    if (!win) {
                    // Renew symbol to empty one
                    checkSymbol = table->getEmptyValue();
                    } else {
                        break;
                    }
                }
            }

            if (!win) {
                // Check diagonally to the left;
                for (unsigned short col_row = 1; col_row <= table->getColumnsNum(); ++col_row) {
                    T symbol = *table->getCellValue(col_row, col_row);
                    if (symbol == table->getEmptyValue()) {
                        win = false;
                        break;
                    } else if (checkSymbol == table->getEmptyValue()) {
                        // What if the table is 1x1? Let's make it a win :P
                        win = true;
                        checkSymbol = symbol;
                    } else if (checkSymbol == symbol) {
                        // Keep the win condition true until something goes wrong.
                        win = true;
                    } else {
                        win = false;
                        break;
                    }
                }

                if (!win) {
                    // Renew symbol to empty one
                    checkSymbol = table->getEmptyValue();
                }
            }

            if (!win) {
                // Check diagonally to the right;
                for (unsigned short row = table->getRowsNum(), column = 1; row != 0; --row, ++column) {
                    T symbol = *table->getCellValue(row, column);
                    if (symbol == table->getEmptyValue()) {
                        win = false;
                        break;
                    } else if (checkSymbol == table->getEmptyValue()) {
                        // What if the table is 1x1? Let's make it a win :P
                        win = true;
                        checkSymbol = symbol;
                    } else if (checkSymbol == symbol) {
                        // Keep the win condition true until something goes wrong.
                        win = true;
                    } else {
                        win = false;
                        break;
                    }
                }
            }

            if (win) {
                this->winner = TicTacToe::checkSymbolForPlayer(checkSymbol);
                return GameStatus::WIN;
            } else if (!anyMovementAvailable()) {
                return GameStatus::DRAW;
            }

            return GameStatus::ONGOING;
        }

        // Get a winner defined after the check.
        const Player<T> * getWinner() {
            return winner;
        }

        virtual ~TicTacToe() {
            for (Player<T> * player : players) {
                delete player;
            }

            players.clear();

            delete table;
        }

    private:
        // Pick a player which the symbol matches.
        Player<T> * checkSymbolForPlayer(T symbol) {
            for (Player<T> * player : players) {
                if (player->getPlayerSymbol() == symbol) {
                    return player;
                }
            }

            return nullptr;
        }

        // Return a std::vector<std::vector<unsigned short>> with
        // all the rows and columns which still have a default type.
        bool anyMovementAvailable() {
            for (unsigned short row = 1; row <= this->table->getRowsNum(); ++row) {
                for (unsigned short column = 1; column <= this->table->getColumnsNum(); ++column) {
                    if (*this->table->getCellValue(row, column) == this->table->getEmptyValue()) {
                        return true;
                    }
                }
            }

            return false;
        }
    };
}

#endif //TICTACTOE_TIC_TAC_TOE_H
