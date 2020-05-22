#include "player.h"
#include "../../exceptions/player/player_exceptions.h"

namespace tic_tac_toe {
    template<class T>
    Player<T>::Player(const T& symbol) {
        if (!verifyIfUsedSymbol(symbol)) {
            this->player_symbol = symbol;
        } else{
            throw UnusableSymbol();
        }
    }

    template<class T>
    Player<T>::~Player() {
        players_symbols.remove(this->player_symbol);
    }

    template<class T>
    bool Player<T>::verifyIfUsedSymbol(const T& symbol) {
        for (const T& list_symbol : players_symbols) {
            if (list_symbol == symbol) {
                return true;
            }
        }

        return false;
    }

    template<class T>
    const T& Player<T>::getPlayerSymbol() {
        return this->player_symbol;
    }

    template<typename T>
    rowsAndColumnsAvailable Player<T>::getAvailableMoves(const PlainTable<T> &table) {
        rowsAndColumnsAvailable availableCells;

        for (unsigned short row = 0; row < table.getRowsNum(); ++row) {
            availableCells.emplace_back(std::vector<unsigned short>());
            for (unsigned short column = 0; column < table.getColumnsNum(); ++column) {
                if (table.getCellValue(row, column) == table.getEmptyValue()) {
                    availableCells[row].emplace_back(column);
                }
            }
        }

        return tic_tac_toe::rowsAndColumnsAvailable();
    }


}