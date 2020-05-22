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
        PlainTable(constUnShort l_rows, constUnShort l_columns, T empty_value = T());

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
         * Return the default or defined empty value for T.
         */
        T getEmptyValue();

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
        void setCellValue(constUnShort row, constUnShort column, T new_value);

        /*
         * Define a new number of columns.
         *
         * Such action will redefine the entire table.
         *
         * new_columns -> new number of columns
         */
        void setColumnsNum(constUnShort new_columns);

        /*
         * Define a new number of rows.
         *
         * Such action will redefine the entire table.
         *
         * new_rows -> new number of rows.
         */
        void setRowsNum(constUnShort new_rows);

        /*
         * Define a new empty value for T type
         *
         * new_empty_value -> said new T empty value.
         */
        void setEmptyValue(T new_empty_value);

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
