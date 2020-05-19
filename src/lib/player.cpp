#include <limits>

#include "player.h"
#include "../exceptions/player/player_exceptions.h"

namespace tic_tac_toe {
    Player::Player() {
         this->player_symbol = this->pickSymbol();
    }

    Player::Player(const unsigned char symbol) {
        this->updateAvailableSymbol(symbol);
    }

    Player::~Player() {
        this->freeSymbol();
    }

    unsigned char Player::pickSymbol() {
        if (!available_symbols) {
            available_symbols = 1;
        }

        if (available_symbols == std::numeric_limits<unsigned char>::max()) {
            throw OutOfSymbols();
        }

        unsigned char symbol = available_symbols;
        ++available_symbols;
        return symbol;
    }

    unsigned char Player::updateAvailableSymbol(unsigned char lastSymbol) {
        if (lastSymbol < available_symbols ||
            lastSymbol == std::numeric_limits<unsigned char>::max()) {
            throw UnusableSymbol();
        }

        available_symbols = lastSymbol + 1;

        return lastSymbol;
    }

    unsigned char Player::getPlayerSymbol() {
        return this->player_symbol;
    }

    void Player::freeSymbol() {
        if (available_symbols - 1 == this->player_symbol) {
            --available_symbols;
        }
    }
}