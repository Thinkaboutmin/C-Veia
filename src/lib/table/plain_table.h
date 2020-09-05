#ifndef TICTACTOE_PLAIN_TABLE_H
#define TICTACTOE_PLAIN_TABLE_H

#include "../exceptions/table/table_exceptions.h"

#include <vector>
#include <limits>
#include <map>

namespace tic_tac_toe {
    using constUnShort = const unsigned short;
    using rowsAndColumns = std::vector<std::vector<unsigned short>>;


    /*
    * A simple table object.
    *
    * The T type is the value which our table will hold inside each cell.
    * Such a type shall have a constructor capable of not accepting any
    * data set.
    */
    template<typename T>
    class PlainTable {

    /**************************************************************
     *                     Variable Definition                    *
     **************************************************************/
    public:
        static constexpr unsigned short max_row_size = std::numeric_limits<unsigned short>::max();
        static constexpr unsigned short max_column_size = std::numeric_limits<unsigned short>::max();
        
    private:
        unsigned short rows = 0;
        unsigned short columns = 0;

        // Total amount of symbols, aka, players on the table.
        std::vector<const T *> symbols_on_table;
        T empty_value;

    protected:
        std::vector<std::vector<const T *>> table_values;

    /**************************************************************
     *                     Function Definition                    *
     **************************************************************/
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

        virtual ~PlainTable() = default;

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
        const T * getCellValue(constUnShort row, constUnShort column) {
            if (row > this->rows || column > this->columns) {
                throw UnavailableCell();
            }

            return this->table_values[row - 1][column - 1];
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
         * new_value -> new value for the cell. Default is empty.
         */
        PlainTable<T> & setCellValue(constUnShort row, constUnShort column, const T * new_value = nullptr) {
            if (new_value == nullptr) {
                new_value = &this->empty_value;
            }
            if ((row > this->rows || column > this->columns) ||
                row == 0 || column == 0) {
                throw UnavailableCell();
            }

            this->table_values[row - 1][column - 1] = new_value;

            if (*new_value != this->empty_value) {
                bool foundSymbol = false;
                for (const T * symbol : this->symbols_on_table) {
                    if (*symbol == *new_value) {
                        foundSymbol = true;
                        break;
                    }
                }

                if (!foundSymbol) {
                    this->symbols_on_table.emplace_back(new_value);
                }
            }

            return *this;
        }

        /*
         * Define a new number of columns.
         *
         * Such action will redefine the entire table.
         *
         * new_columns -> new number of columns
         */
        PlainTable<T> & setColumnsNum(constUnShort new_columns) {
            if (new_columns == 0) {
                throw ColumnIsZero();
            }

            if (new_columns != this->columns) {
                unsigned short rest_columns = this->columns;
                this->columns = new_columns;
            }

            return *this;
        }

        /*
         * Define a new number of rows.
         *
         * Such action will redefine the entire table.
         *
         * new_rows -> new number of rows.
         */
        PlainTable<T> & setRowsNum(constUnShort new_rows) {
            if (new_rows == 0) {
                throw RowIsZero();
            }

            if (new_rows != this->rows) {
                unsigned short rest_rows = this->rows;
                this->rows = new_rows;
            }

            return *this;
        }

        /*
         * Define a new empty value for T type
         *
         * new_empty_value -> said new T empty value.
         */
        PlainTable<T> & setEmptyValue(T new_empty_value) {
            this->empty_value = new_empty_value;

            return *this;
        }

        /*
         * Clear all values in the table by generating
         * a new table.
         */
        PlainTable<T> & clearValues() {
            generateValueTable();

            return *this;
        }

        /*
         * Generate a map of all the player cells.
         * 
         * The value inside a key is a vector, which are rows and the vectors inside those rows
         * are the columns position. 
         *
         * Note that even if the row doesn't have any
         * value it will be on the row vector but without any column position.
         */
        const std::map<const T *, rowsAndColumns> getSymbolsCells() {
            std::map<const T *, rowsAndColumns> player_cells;
            // Prepare player cells.
            for (const T * symbol : this->symbols_on_table) {
                player_cells[symbol] = std::vector<std::vector<unsigned short>>();
            }
            

            for (unsigned short row = 1; row <= this->rows; ++row) {
                for (auto map_symbol : player_cells) {
                    player_cells[map_symbol.first].emplace_back(std::vector<unsigned short>());
                }

                for (unsigned short column = 1; column <= this->columns; ++column) {
                    const T * player_symbol = this->getCellValue(row, column);
                    if (*player_symbol != this->empty_value) {
                        // Although pointers can differ in address or its pointed address, this is
                        // not expected here at least, so it should work.
                        player_cells[player_symbol][row - 1].emplace_back(column);
                    }
                }
            }

            return player_cells;
        }

        /*
         * Return a std::vector<std::vector<unsigned short>> with
         * all the rows and columns which still have a default type.
         */ 
        rowsAndColumns getEmptyCells() {
            rowsAndColumns availableCells;

            for (unsigned short row = 1; row <= this->rows; ++row) {
                availableCells.emplace_back(std::vector<unsigned short>());
                for (unsigned short column = 1; column <= this->columns; ++column) {
                    if (*this->table_values[row - 1][column - 1] == this->empty_value) {
                        availableCells[row - 1].emplace_back(column);
                    }
                }
            }

            return availableCells;
        }

        static rowsAndColumns convertRowsColumnsToColumnsRows(const rowsAndColumns & data) {
            rowsAndColumns columns_rows;
            if (data.size() == 0) {
                return columns_rows;
            }
            columns_rows.resize(data.size());
            for (unsigned short column = 1; column <= data.size(); ++column) {
                if (data[column - 1].size() != 0) {
                    for (unsigned short row = 1; row <= data.size(); ++row) {
                        for (const unsigned short column_verifier : data[row - 1]) {
                            if (column_verifier == column) {
                                columns_rows[column - 1].emplace_back(row);
                                break;
                            }
                        }
                    }
                }
            }

            return columns_rows;
        }

    protected:
        /*
         * Generate the value table with default values.
         *
         * Remember, T type shall accept a constructor without parameter.
         */
        PlainTable<T> & generateValueTable() {
            if (!this->table_values.empty()) {
                this->table_values.clear();
            }

            for (unsigned short row = 0; row < this->rows; ++row) {
                this->table_values.emplace_back(std::vector<const T *>());
                for (unsigned short column = 0; column < this->columns; ++column) {
                    this->table_values[row].emplace_back(&empty_value);
                }
            }

            return *this;
        }
    };
}

#endif //TICTACTOE_PLAIN_TABLE_H
