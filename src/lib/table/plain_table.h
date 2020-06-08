#ifndef TICTACTOE_PLAIN_TABLE_H
#define TICTACTOE_PLAIN_TABLE_H

#include <vector>
#include "../exceptions/table/table_exceptions.h"

namespace tic_tac_toe {
    using constUnShort = const unsigned short;

/*
 * A simple table object.
 *
 * The T type is the value which our table will hold inside each cell.
 * Such a type shall have a constructor capable of not accepting any
 * data set.
 */
    template<typename T>
    class PlainTable {
    private:
        unsigned short rows = 0;
        unsigned short columns = 0;
        T empty_value;

    protected:
        std::vector<std::vector<T>> table_values;

    public:
        /*
         * l_rows -> Define the number of rows of the table
         * l_columns -> Define the number of columns of the table
         */
        PlainTable(constUnShort l_rows, constUnShort l_columns, T empty_value = T()) {
            if (l_rows == 0) {
                throw RowIsZero();
            }
            this->rows = l_rows;

            if (l_columns == 0) {
                throw ColumnIsZero();
            }
            this->columns = l_columns;
            this->empty_value = empty_value;

            this->generateValueTable();
        }

        /*
         * Return the total number of rows.
         */
        unsigned short getRowsNum() {
            return this->rows;
        }

        /*
         * Return the total number of columns.
         */
        unsigned short getColumnsNum() {
            return this->columns;
        }

        /*
         * Return the cell value at a given row and column.
         *
         * If a row and column was given beyond the value a
         * UnavailableCell error will be throw.
         */
        T getCellValue(constUnShort row, constUnShort column) {
            if (row >= this->rows || column >= this->columns) {
                throw UnavailableCell();
            }

            return this->table_values[row][column];
        }

        /*
         * Return the default or defined empty value for T.
         */
        T getEmptyValue() {
            return this->empty_value;
        }

        /*
         * Set the cell value at a given row and column.
         *
         * If a row and column was given beyond the value a
         * UnavailableCell error will be throw.
         *
         * row -> the row which the cell is located
         * column -> the column which the cell is located
         * new_value -> new value for the cell.
         */
        void setCellValue(constUnShort row, constUnShort column, T new_value) {
            if (row >= rows || column >= this->columns) {
                throw UnavailableCell();
            }

            this->table_values[row][column] = new_value;
        }

        /*
         * Define a new number of columns.
         *
         * Such action will redefine the entire table.
         *
         * new_columns -> new number of columns
         */
        void setColumnsNum(constUnShort new_columns) {
            if (new_columns == 0) {
                throw ColumnIsZero();
            }

            if (new_columns != this->columns) {
                unsigned short rest_columns = this->columns;
                this->columns = new_columns;
            }
        }

        /*
         * Define a new number of rows.
         *
         * Such action will redefine the entire table.
         *
         * new_rows -> new number of rows.
         */
        void setRowsNum(constUnShort new_rows) {
            if (new_rows == 0) {
                throw RowIsZero();
            }

            if (new_rows != this->rows) {
                unsigned short rest_rows = this->rows;
                this->rows = new_rows;
            }
        }

        /*
         * Define a new empty value for T type
         *
         * new_empty_value -> said new T empty value.
         */
        void setEmptyValue(T new_empty_value) {
            this->empty_value = new_empty_value;
        }

    protected:
        /*
         * Generate the value table with default values.
         *
         * Remember, T type shall accept a constructor without parameter.
         */
        void generateValueTable() {
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
    };
}

#endif //TICTACTOE_PLAIN_TABLE_H