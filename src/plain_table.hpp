#ifndef TICTACTOE_PLAIN_TABLE_HPP
#define TICTACTOE_PLAIN_TABLE_HPP

#include <vector>

/*
 * A simple table object.
 *
 * The T type is the value which our table will hold inside each cell.
 * Such a type shall have a constructor capable of not accepting any
 * data set.
 */
template<typename T> class PlainTable {
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
    PlainTable(unsigned short l_rows, unsigned short l_columns);

    /*
     * Return the total number of rows.
     */
    unsigned short getRowsNum();

    /*
     * Return the total number of columns.
     */
    unsigned short getColumnsNum();

    T getCellValue(unsigned short row, unsigned short column);

    T setCellValue(unsigned short row, unsigned  short column);

    /*
     * Define again the number of columns.
     *
     * Such action will redefine the entire table.
     *
     * l_columns -> new number of columns
     */
    void setColumnsNum(unsigned short l_columns);

    /*
     * Define again the number of rows.
     *
     * Such action will redefine the entire table.
     *
     * l_rows -> new number of rows.
     */
    void setRowsNum(unsigned short l_rows);

protected:
    /*
     * Generate the value table with default values.
     *
     * Remember, T type shall accept a constructor without parameter.
     */
    void generateValueTable();

    /*
     * Regenerate the value of the table.
     *
     * Such regeneration will trim any value that is outside of the scope
     * leaving only the set ones.
     *
     *
     * Example: + value already set and - not.
     *
     * Table: + + + (1 row and 3 columns)
     * But now it was set with the following value:
     * Table: + + + - (1 row and 4 columns)
     * And
     * Table: + + (1 row and 2 columns)
     *
     * old_rows -> Old value of the table. If nullptr is set it will be ignored.
     * old_columns -> Old value of the table. If nullptr is set it will be ignored.
     */
    void regenerateValueTable(unsigned short *old_rows = nullptr, unsigned short *old_columns = nullptr);
};


#endif //TICTACTOE_PLAIN_TABLE_HPP
