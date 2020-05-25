#include <string>

#include "string_table.h"

namespace tic_tac_toe {
    StringTable::StringTable(constUnShort rows, constUnShort columns) : PlainTable<std::wstring>(rows, columns) {
    }

    std::wstring StringTable::tableString() {
        std::wstring table;

        // Kamehameha!!! Sry...
        if (this->getColumnsNum() != 0 && this->getRowsNum() != 0) {
            for (unsigned short row_x = 0; row_x < this->getRowsNum(); ++row_x) {
                for (unsigned short column_y = 0; column_y < this->getColumnsNum(); ++column_y) {
                    table = L" " + getCellValue(row_x, column_y) + L" ";

                    // Verify if it is the last column meaning that there should not
                    // be a divisor for the table.
                    if (column_y + 1 != this->getColumnsNum()) {
                        table += L"\u2551";

                        // Same but with the row. We will add the bottom divisor.
                        if (row_x + 1 != this->getRowsNum()) {
                            table += L"\u2550\u2550\u2550\u256c";
                        } else {
                            table += L"\u2550\u2550\u2550";
                        }
                    }
                }
            }
        }

        return table;
    }
}