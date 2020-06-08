#include "utils.h"

#include <vector>
#include <iostream>

void clearScreen() {
    for (unsigned short i = 0; i < 256; ++i) {
        std::cout << "\n";
    }
}

void setPlace(unsigned short row, unsigned short column) {
    std::cout << "\033[" << row << ";" << column << "H";
}