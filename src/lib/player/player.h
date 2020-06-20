    #ifndef TICTACTOE_PLAYER_H
    #define TICTACTOE_PLAYER_H

    #include <limits>
    #include <list>
    #include <string>

    #include "../table/plain_table.h"
    #include "player_move.h"
    #include "../exceptions/player/player_exceptions.h"

    namespace tic_tac_toe {
    using rowsAndColumns = std::vector<std::vector<unsigned short>>;

    /*
    * Players of the tic tac toe game.
    *
    * Symbols for each player should be different from others players
    * otherwise an UnusableSymbol exception will be thrown.
    *
    * The symbol is freed after the Player deleter is called.
    */
    template<typename T>
    class Player {

    /**************************************************************
        *                     Variable Definition                    *
        **************************************************************/
    private:
        static std::list<T> players_symbols;
        T player_symbol;

    /**************************************************************
        *                     Function Definition                    *
        **************************************************************/
    public:
        // Return the player symbol.
        const T & getPlayerSymbol() const {
            return this->player_symbol;
        }

        /*
        * Set the player symbol while veryfing if such
        * is used. If used, UnsuableSymbol exception will be thrown.
        */
        void setPlayerSymbol(T & symbol) {
            if (!verifyIfUsedSymbol(symbol)) {
                this->player_symbol = symbol;
            } else {
                throw UnusableSymbol();
            }
        }

        // Make the player act by getting its move intent.
        virtual PlayerMove<T> getMove(PlainTable<T> &table) = 0;

        virtual ~Player() {
            Player<T>::players_symbols.remove(this->player_symbol);
        }
    protected:
        // Verify in our list of player symbols if there's match. If so,
        // returns true otherwise false.
        static bool verifyIfUsedSymbol(const T& symbol) {
            for (const T& list_symbol : Player<T>::players_symbols) {
                if (list_symbol == symbol) {
                    return true;
                }
            }

            return false;
        }

        // Return a std::vector<std::vector<unsigned short>> with
        // all the rows and columns which still have a default type.
        static rowsAndColumns getAvailableMoves(PlainTable<T> &table) {
            rowsAndColumns availableCells;

            for (unsigned short row = 1; row <= table.getRowsNum(); ++row) {
                availableCells.emplace_back(std::vector<unsigned short>());
                for (unsigned short column = 1; column <= table.getColumnsNum(); ++column) {
                    if (*table.getCellValue(row, column) == table.getEmptyValue()) {
                        availableCells[row - 1].emplace_back(column);
                    }
                }
            }

            return availableCells;
        }

        Player(const T& symbol) {
            if (!verifyIfUsedSymbol(symbol)) {
                this->player_symbol = symbol;
            } else {
                throw UnusableSymbol();
            }
        }
    };

    template<class T>
    std::list<T> Player<T>::players_symbols;
    }


    #endif //TICTACTOE_PLAYER_H
