#include "plain_table.hpp"

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
        unsigned short restColumns =
        this->columns = l_columns;

        this->tableReset(this->rows, restColumns);
    }
}

template<class T>
void PlainTable<T>::setRowsNum(unsigned short l_rows) {
    if (l_rows != this->rows) {
        unsigned short restRows = this->rows;
        this->rows = l_rows;

        this->tableReset(restRows, this->columns);
    }
}

template<class T>
void PlainTable<T>::generateValueTable(unsigned short *old_rows, unsigned short *old_columns) {
    // TODO
}
