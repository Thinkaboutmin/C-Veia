#include "player.h"
#include "../../exceptions/player/player_exceptions.h"

namespace tic_tac_toe {
    Player::Player(const std::wstring& symbol) {
        if (!verifyIfUsedSymbol(symbol)) {
            this->player_symbol = symbol;
        } else{
            throw UnusableSymbol();
        }
    }

    Player::~Player() {
        players_symbols.remove(this->player_symbol);
    }

    bool Player::verifyIfUsedSymbol(const std::wstring& symbol) {
        for (const std::wstring& list_symbol : players_symbols) {
            if (list_symbol == symbol) {
                return true;
            }
        }

        return false;
    }

    std::wstring Player::getPlayerSymbol() {
        return this->player_symbol;
    }
}