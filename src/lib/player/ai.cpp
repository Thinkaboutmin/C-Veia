#include "ai.h"

#include <random>
#include <chrono>

namespace tic_tac_toe {
    template<class T>
    AI<T>::AI(T symbol, difficulty dif) : Player<T>(symbol){
        if (difficultyIsValid(dif)) {
            this->type = dif;
        } else {
            throw UnknownDifficulty();
        }
    }

    template<class T>
    void AI<T>::setDifficulty(difficulty dif) {
        if (difficultyIsValid(dif)) {
            this->type = dif;
        } else {
            throw UnknownDifficulty();
        }
    }

    template<class T>
    bool AI<T>::difficultyIsValid(difficulty dif) {
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

    template<class T>
    const difficulty& AI<T>::getDifficulty() {
        return this->type;
    }

    template<class T>
    PlayerMove<T> AI<T>::getMove(const PlainTable<T> &table) {
        switch (this->type) {
            case difficulty::DEFAULT:
            case difficulty::NORMAL:
                return this->normalMove();
            case difficulty::EASY:
                return this->easyMove();
            case difficulty::HARD:
                return this->hardMove();
            default:
                // Throwing an error here seems misleading and breaks
                // the design of the application for now it will be kept.
                throw UnknownDifficulty();
        }
    }

    using shortDistributor = std::uniform_int_distribution<unsigned short>;
    template<typename T>
    PlayerMove<T> AI<T>::easyMove(const PlainTable<T> &table) {
        std::mt19937_64 generator;
        generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
        shortDistributor distributeColumn(0, table.getColumnsNum());
        // TODO: Implement a way to pick from the available cells vector.

    }

    template<typename T>
    PlayerMove<T> AI<T>::normalMove(const PlainTable<T> &table) {
        return PlayerMove<T>(0, 0, T());
    }

    template<typename T>
    PlayerMove<T> AI<T>::hardMove(const PlainTable<T> &table) {
        return PlayerMove<T>(0, 0, T());
    }
}