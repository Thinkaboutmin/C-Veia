#ifndef TICTACTOE_TIC_TAC_TOE_H
#define TICTACTOE_TIC_TAC_TOE_H

#include <vector>

#include "../player/player.h"
#include "../table/plain_table.h"
#include "../../exceptions/tic_tac_toe/tic_tac_toe_exceptions.h"

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
        using playerIterator = std::vector<Player<T>, std::allocator<Player<T>>>;
    private:
        const std::vector<const Player<T>> players;
        playerIterator playerToPlay;
        const PlainTable<T> table;
        Player<T> * winner = nullptr;

    public:
        /*
         * Constructor
         *
         * players -> An ordered list of players. The first there is the first to play.
         * table -> The actual table in which the game should occur.
         */
        TicTacToe(std::vector<Player<T>> players, PlainTable<T> table) :
                 table(table), players(players) {
            if (this->players.empty()) {
                throw NotEnoughPlayers();
            }

            // Make sure that each player have a different symbol.
            for (Player<T> player : this->players) {
                if (player.getPlayerSymbol() == table.getEmptyValue()) {
                    throw EmptyValueConflict();
                }
            }

            if (this->table.getRowsNum() != this->table.getColumnsNum()) {
                throw TableIsNotEqualInSides();
            }
        }

        void playerPlay() {
            PlayerMove<T> move = getNextPlayer().getMove(table);
            table.setCellValue(move.row, move.column, move.value);
        }

        // Return the next player of our vector.
        const Player<T>& getNextPlayer() {
            if (playerToPlay == players.end()) {
                playerToPlay = players.begin();
            }

            const Player<T> & player = playerToPlay;
            ++playerToPlay;
            return player;
        }

        // Verifies for the given table for a winner.
        bool isThereAWinner() {
            T checkSymbol = table.getEmptyValue();

            bool win = false;
            // Check each column in a row for a horizontal win.
            for (unsigned short row = 0; row < table.getRowsNum(); ++row) {
                for (unsigned short column = 0; column < table.getColumnsNum(); ++column) {
                    T symbol = table.getCellValue(row, column);
                    if (symbol == table.getEmptyValue()) {
                        win = false;
                        break;
                    } else if (checkSymbol == table.getEmptyValue()) {
                        // What is the table is 1x1? Let's make it a win :P
                        win = true;
                        checkSymbol = symbol;
                    } else {
                        // Keep the win condition true until something goes wrong.
                        win = true;
                    }
                }

                if (win) {
                    this->winner = checkSymbolForPlayer(checkSymbol);
                    return win;
                }
                // Renew symbol to empty one.
                checkSymbol = table.getEmptyValue();
            }

            if (!win) {
                // Check for each row in a column for a vertical win.
                for (unsigned short column = 0; column < table.getColumnsNum(); ++column) {
                    for (unsigned short row = 0; row < table.getRowsNum(); ++row) {
                        T symbol = table.getCellValue(row, column);
                        if (symbol == table.getEmptyValue()) {
                            win = false;
                            break;
                        } else if (checkSymbol == table.getEmptyValue()) {
                            // What if the table is 1x1? Let's make it a win :P
                            win = true;
                            checkSymbol = symbol;
                        } else {
                            // Keep the win condition true until something goes wrong.
                            win = true;
                        }
                    }
                    // Renew symbol to empty one.
                    checkSymbol = table.getEmptyValue();
                }
            }

            if (!win) {
                // Check diagonally to the left;
                for (unsigned short col_row = 0; col_row < table.getColumnsNum(); ++col_row) {
                    T symbol = table.getCellValue(col_row, col_row);
                    if (symbol == table.getEmptyValue()) {
                        win = false;
                        break;
                    } else if (checkSymbol == table.getEmptyValue()) {
                        // What if the table is 1x1? Let's make it a win :P
                        win = true;
                        checkSymbol = symbol;
                    } else {
                        // Keep the win condition true until something goes wrong.
                        win = true;
                    }
                }

                // Renew symbol to empty one
                checkSymbol = table.getEmptyValue();
            }

            if (!win) {
                // Check diagonally to the right;
                for (unsigned short col_row = table.getRowsNum(); col_row != 0; --col_row) {
                    T symbol = table.getCellValue(col_row, col_row);
                    if (symbol == table.getEmptyValue()) {
                        win = false;
                        break;
                    } else if (checkSymbol == table.getEmptyValue()) {
                        // What if the table is 1x1? Let's make it a win :P
                        win = true;
                        checkSymbol = symbol;
                    } else {
                        // Keep the win condition true until something goes wrong.
                        win = true;
                    }
                }
            }

            if (win) {
                this->winner = checkSymbolForPlayer(checkSymbol);
                return win;
            }

            return false;
        }

        // Get a winner defined after the check.
        const Player<T> * getWinner() {
            return winner;
        }

    private:
        // Pick a player which the symbol matches.
        Player<T> checkSymbolForPlayer(T symbol) {
            for (Player<T> player : players) {
                if (player.getPlayerSymbol() == symbol) {
                    return player;
                }
            }
        }
    };
}

#endif //TICTACTOE_TIC_TAC_TOE_H
