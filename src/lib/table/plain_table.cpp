#include <vector>

#include "plain_table.hpp"
#include "../../exceptions/table/table_exceptions.h"
namespace tic_tac_toe {
    template<class T>
    PlainTable<T>::PlainTable(constUnShort l_rows, constUnShort l_columns, T empty_value) {
        this->rows = l_rows;
        this->columns = l_columns;
        this->empty_value = empty_value;

        this->generateValueTable();
    }

    template<class T>
    unsigned short PlainTable<T>::getColumnsNum() {
        return this->columns;
    }

    template<class T>
    unsigned short PlainTable<T>::getRowsNum() {
        return this->rows;
    }

    template<class T>
    void PlainTable<T>::setColumnsNum(constUnShort new_columns) {
        if (new_columns != this->columns) {
            unsigned short rest_columns = this->columns;
            this->columns = new_columns;
        }
    }

    template<class T>
    void PlainTable<T>::setRowsNum(constUnShort new_rows) {
        if (new_rows != this->rows) {
            unsigned short rest_rows = this->rows;
            this->rows = new_rows;
        }
    }

    template<class T>
    void PlainTable<T>::generateValueTable() {
        if (!this->table_values.empty()) {
            this->table_values.clear();
        }

        for (unsigned short row = 0; row < this->rows; ++row) {
            this->table_values.emplace_back(std::vector<T>());
            for (unsigned short column = 0; column < this->columns; ++column) {
                this->table_values[row].emplace_back(T());
            }
        }
    }

    template<class T>
    T PlainTable<T>::getCellValue(constUnShort row, constUnShort column) {
        if (row >= this->rows || column >= this->columns) {
            throw UnavailableCell();
        }

        return this->table_values[row][column];
    }

    template<class T>
    void PlainTable<T>::setCellValue(constUnShort row, constUnShort column, T new_value) {
        if (row >= rows || column >= this->columns) {
            throw UnavailableCell();
        }

        this->table_values[row][column] = new_value;
    }

    template<typename T>
    void PlainTable<T>::setEmptyValue(T new_empty_value) {
        this->empty_value = new_empty_value;
    }

    template<typename T>
    T PlainTable<T>::getEmptyValue() {
        return this->empty_value;
    }
}