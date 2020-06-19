#include "screen.h"

#include <vector>
#include <string>
#include <iostream>
#include <limits>

Screen::Screen(std::wostream & output, std::wistream & input) : output(output), input(input) {
	this->clearScreen();
	this->setPlace(this->cursor_row, this->cursor_column);
}

// Delegate to Screen(output, input).
Screen::Screen(std::wistream & input, std::wostream & output) : Screen(output, input) {}


Screen & Screen::clearLine() {
	// Ansi clear line command.
	this->output << L"\033[2K";
	this->cursor_column = 0;
	this->setPlace(this->cursor_row, this->cursor_column);
	return *this;
}

Screen & Screen::clearScreen() {
	// Ansi clear screen command.
	this->output << L"\033[2J";
	this->cursor_column = 1;
	this->cursor_row = 1;
	this->setPlace(this->cursor_row, this->cursor_column);

	return *this;
}

const unsigned int & Screen::getColumn() {
	return this->cursor_column;
}

std::wstring Screen::getLine() {
	std::wstring string_out;
	std::getline(this->input, string_out);

	++this->cursor_row;
	this->cursor_column = string_out.size();

	return string_out;
}

const unsigned int & Screen::getRow() {
	return this->cursor_row;
}

Screen & Screen::print(const std::wstring &string) {
	this->output << string;
	size_t max_size = std::numeric_limits<size_t>::max();
	size_t index = 0;

	while (true) {
		size_t last_index = index;
		index = string.find(L'\n', index);

		if (index != max_size) {
			index += 1;
			// Each new line is a new row, right?
			++this->cursor_row;
		} else {
			index = last_index;
			break;
		}
	}

	this->cursor_column = string.size() - index;

	return *this;
}

Screen & Screen::setPlace(unsigned int row, unsigned int column) {
	// Do not accept 0 row and column.
	row = !row ? 1: row;
	column = !column ? 1 : column;
	this->cursor_row = row; 
	this->cursor_column = column;
	this->output << L"\033[" << this->cursor_row << L";" << this->cursor_column << L"H";
	return *this;
}

Screen & Screen::print(const int & number) {
	std::wstring s_number = std::to_wstring(number);

	this->output << s_number;
	this->cursor_column = s_number.size();

	return *this;
}

int Screen::getInt() {
	unsigned int column = this->cursor_column;
	unsigned int row = this->cursor_row;
	
	int number = 0;
	bool had_error = false;
	unsigned int number_length = 0;
	do {
		std::wstring s_number = this->getLine();
		number_length = s_number.size();
		try {
			number = std::stoi(s_number);
			break;
		} catch(std::invalid_argument & _) {
			this->print(L"\n\n");
			this->clearLine();
			this->print(L"Type a number");
			this->setPlace(row, 1).clearColumnRange(column, column + number_length);
			had_error = true;
			continue;
		} catch(std::out_of_range & _) {
			this->print(L"\n\n");
			this->clearLine();
			this->print(L"Invalid number range");
			this->setPlace(row, 1).clearColumnRange(column, column + number_length);
			had_error = true;			
			continue;
		}
	} while (true);

	if (had_error) {
		column = this->cursor_column;
		row = this->cursor_row;
		this->setPlace(row + 2, 1);
		this->clearLine();
		this->setPlace(row, column);
	}

	return number;
}

Screen & Screen::clearColumnRange(unsigned int column_x, unsigned int column_y) {
	column_x = !column_x ? 1 : column_x;
	column_y = !column_y ? 1 : column_y;

	unsigned int dif = 0;
	
	if (column_y >= column_x) {
		this->setPlace(this->cursor_row, column_x);
		dif = column_y - column_x + 1;
	} else {
		this->setPlace(this->cursor_row, column_y);
		dif = column_x - column_y + 1;
	}

	std::wstring spaces;
	spaces.insert(spaces.begin(), dif, L' ');
	this->output << spaces;
	this->setPlace(this->cursor_row, column_x);

	return *this;
}
