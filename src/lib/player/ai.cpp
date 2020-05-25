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
        rowsAndColumns available_cells = Player<T>::getAvailableMoves(table);
        // As we erase cells we will need to have a ordered list
        // which holds data about the available rows index.
        std::vector<unsigned short> available_rows;
        for (unsigned short index_row = 0; index_row < table.getRowsNums(); ++index_row) {
            available_rows.emplace_back(index_row);
        }

        // Prepare random number generation.
        std::mt19937_64 generator(std::chrono::system_clock::now().time_since_epoch().count());
        shortDistributor dist(0,  available_rows.size() - 1);

        while(true) {
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
                return PlayerMove<T>(true_row, available_cells[row], this->getPlayerSymbol());
            }

            dist.param(shortDistributor::param_type(0, columns - 1));
            unsigned short column = dist(generator);

            return PlayerMove<T>(true_row, column, this->getPlayerSymbol());
        }
    }

    template<typename T>
    PlayerMove<T> AI<T>::normalMove(const PlainTable<T> &table) {
        return PlayerMove<T>(0, 0, T());
    }

    template<typename T>
    PlayerMove<T> AI<T>::hardMove(const PlainTable<T> &table) {
        rowsAndColumns available_cells = Player<T>::getAvailableMoves();

        return PlayerMove<T>(0, 0, T());
    }
}