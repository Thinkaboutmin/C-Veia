#include <string>

#include "string_table.h"

namespace tic_tac_toe {
    StringTable::StringTable(constUnShort rows, constUnShort columns) : PlainTable<std::wstring>(rows, columns, L" ") {
    }

    std::wstring StringTable::tableString() {
        std::wstring table;

        // Kamehameha!!! Sry...
        if (this->getColumnsNum() != 0 && this->getRowsNum() != 0) {
            for (unsigned short row_x = 1; row_x <= this->getRowsNum(); ++row_x) {
                std::wstring downDivisor;
                for (unsigned short column_y = 1; column_y <= this->getColumnsNum(); ++column_y) {
                    table += L" " + *getCellValue(row_x, column_y) + L" ";

                    // Verify if it is the last column meaning that there should not
                    // be a divisor for the table.
                    // Same but with the row. We will add the bottom divisor.
                    if (column_y != this->getRowsNum()) {
                        table += L"\u2551";
                        downDivisor += L"\u2550\u2550\u2550\u256c";
                    } else {
                        downDivisor += L"\u2550\u2550\u2550";
                    }
                }
                // Check if this is the last run. If so, do not add
                // bottom divisor.
                if (row_x + 1 <= this->getRowsNum()) {
                    table += L"\n" + downDivisor + L"\n";
                }
            }
        }

        table += L"\n\n";

        return table;
    }
}