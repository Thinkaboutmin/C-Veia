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


}