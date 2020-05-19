#ifndef TICTACTOE_PLAIN_TABLE_HPP
#define TICTACTOE_PLAIN_TABLE_HPP

#include <vector>

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
// ************************* Variables *************************
    private:
        unsigned short rows = 0;
        unsigned short columns = 0;

    protected:
        std::vector<std::vector<T>> table_values;

    public:
        /*
         * l_rows -> Define the number of rows of the table
         * l_columns -> Define the number of columns of the table
         */
        PlainTable(constUnShort l_rows, constUnShort l_columns);

        /*
         * Return the total number of rows.
         */
        unsigned short getRowsNum();

        /*
         * Return the total number of columns.
         */
        unsigned short getColumnsNum();

        /*
         * Return the cell value at a given row and column.
         *
         * If a row and column was given beyond the value a
         * UnavailableCell error will be throw.
         */
        T getCellValue(constUnShort row, constUnShort column);

        /*
         * Set the cell value at a given row and column.
         *
         * If a row and column was given beyond the value a
         * UnavailableCell error will be throw.
         */
        void setCellValue(constUnShort row, constUnShort column, T value);

        /*
         * Define again the number of columns.
         *
         * Such action will redefine the entire table.
         *
         * l_columns -> new number of columns
         */
        void setColumnsNum(constUnShort l_columns);

        /*
         * Define again the number of rows.
         *
         * Such action will redefine the entire table.
         *
         * l_rows -> new number of rows.
         */
        void setRowsNum(constUnShort l_rows);

    protected:
        /*
         * Generate the value table with default values.
         *
         * Remember, T type shall accept a constructor without parameter.
         */
        void generateValueTable();
    };
}

#endif //TICTACTOE_PLAIN_TABLE_HPP
