#ifndef TICTACTOE_STRING_TABLE_HPP
#define TICTACTOE_STRING_TABLE_HPP

#include "../lib/table/plain_table.hpp"
#include <string>
namespace tic_tac_toe {
    // A wide string table.
    class StringTable : PlainTable<std::wstring> {
    public:
        StringTable(constUnShort rows, constUnShort columns) : PlainTable<std::wstring>(rows, columns){}

        /*
         * Generate a wide string table.
         */
        std::wstring tableString();
    };
}
#endif //TICTACTOE_STRING_TABLE_HPP
