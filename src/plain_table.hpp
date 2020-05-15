#ifndef TICTACTOE_PLAIN_TABLE_HPP
#define TICTACTOE_PLAIN_TABLE_HPP

#include <vector>

/*
 * A simple table object.
 *
 * The T type is the value which our table will hold inside each cell.
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

    unsigned short getRowsNum();

    unsigned short getColumnsNum();

    T getCellValue(unsigned short row, unsigned short column);

    T setCellValue(unsigned short row, unsigned  short column);

    void setColumnsNum(unsigned short l_columns);

    void setRowsNum(unsigned short l_rows);

protected:
    void generateValueTable(unsigned short *old_rows = nullptr, unsigned short *old_columns = nullptr);
};


#endif //TICTACTOE_PLAIN_TABLE_HPP
