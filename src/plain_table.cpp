#include "plain_table.hpp"
#include <vector>

template<class T>
PlainTable<T>::PlainTable(unsigned short l_rows, unsigned short l_columns) {
    this->rows = l_rows;
    this-> columns = l_columns;
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
void PlainTable<T>::setColumnsNum(unsigned short l_columns) {
    if (l_columns != this->columns) {
        unsigned short rest_columns = this->columns;
        this->columns = l_columns;

        this->generateValueTable(nullptr, rest_columns);
    }
}

template<class T>
void PlainTable<T>::setRowsNum(unsigned short l_rows) {
    if (l_rows != this->rows) {
        unsigned short restRows = this->rows;
        this->rows = l_rows;

        // Regenerate it.
        this->generateValueTable(restRows);
    }
}

template<class T>
void PlainTable<T>::generateValueTable() {
    for (unsigned short row = 0; row < this->rows; ++row) {
        this->table_values.emplace_back(std::vector<T>());
        for (unsigned short column = 0; column < this->columns; ++column) {
            this->table_values[row].emplace_back(T());
        }
    }
}
