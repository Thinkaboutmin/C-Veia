#ifndef TICTACTOE_STRING_TABLE_H
#define TICTACTOE_STRING_TABLE_H

#include <string>

#include "../lib/table/plain_table.h"

namespace tic_tac_toe {
    // A wide string table.
    class StringTable : public PlainTable<std::wstring> {
    public:
        StringTable(constUnShort rows, constUnShort columns);

        /*
         * Generate a wide string table.
         */
        std::wstring tableString();
    };
}
#endif //TICTACTOE_STRING_TABLE_H
