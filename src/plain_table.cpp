#include <vector>

#include "plain_table.hpp"
#include "exceptions/table/table_exceptions.h"

template<class T>
PlainTable<T>::PlainTable(constUnShort l_rows, unsigned short l_columns) {
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
void PlainTable<T>::setColumnsNum(constUnShort l_columns) {
    if (l_columns != this->columns) {
        unsigned short rest_columns = this->columns;
        this->columns = l_columns;

        this->generateValueTable(nullptr, rest_columns);
    }
}

template<class T>
void PlainTable<T>::setRowsNum(constUnShort l_rows) {
    if (l_rows != this->rows) {
        unsigned short restRows = this->rows;
        this->rows = l_rows;

        // Regenerate it.
        this->generateValueTable(restRows);
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
void PlainTable<T>::setCellValue(constUnShort row, constUnShort column, T value) {
    if (row >= rows || column >= this->columns) {
        throw UnavailableCell();
    }

    this->table_values[row][column] = value;
}

template<class T>
void PlainTable<T>::regenerateValueTable(constUnShort *old_rows, constUnShort *old_columns) {
   // TODO: Do we need to regenerate the table value?
}