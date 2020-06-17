#ifndef TICTACTOE_SCREEN_H
#define TICTACTOE_SCREEN_H

#include <iostream>
#include <string>

/*
 * A simple screen representation.
 *
 * It's useful to keep track of where the user cursor is and to acess ansi
 * codes without having to retype or memorize it.
 */
class Screen {
private:
    std::wostream &output;
    std::wistream &input;
    unsigned int cursor_column = 1;
    unsigned int cursor_row = 1;

public:
    Screen(std::wistream & input, std::wostream & output); 

    Screen(std::wostream & output, std::wistream & input);

    /*
    * "Clear" the screen.
    *
    * In reality, it just prints a bunch of new lines.
    */
    Screen & clearScreen();

    /*
     * Clear a line.
     *
     * Be sure to be on the desired line.
     */
    Screen & clearLine();

    /*
     * Use the ansi command character to control the cursor position.
	 *
	 * row -> the column which the cursor will be put.
	 * column -> the column which the cursor will be put.
	 *
	 * Example grid:
	 *   	Column Column
	 *    	  |    |
	 *  	---------
	 * Row 	|   |   |
	 * Row 	|   | X |
	 * Row 	|   |   |
	 *  	---------
	 *  
	 *  In this grid the cursor is at row 2 and column 2 hence setPlace(2,2).
     */
    Screen & setPlace(const unsigned int row, const unsigned int column);

	/*
	 * Get the column position of the cursor.
	 */
    const unsigned int & getColumn();

	/*
	 * Get the row position of the cursor.
	 */
    const unsigned int & getRow();

	/*
	 * Get a line, emphasis on line, from the input stream.
	 */
	std::wstring getLine();

	/*
	 * Prints a string on the output stream.
	 */
	Screen & print(const std::wstring &string);
};

#endif //TICTACTOE_SCREEN_H
