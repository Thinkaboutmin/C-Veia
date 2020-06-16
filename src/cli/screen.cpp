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
	this->cursor_column = 0;
	this->cursor_row = 0;
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
		index = string.find(L'\n', index);

		if (index != max_size) {
			index += 1;
			// Each new line is a new row, right?
			++this->cursor_row;
		} else {
			break;
		}
	}

	this->cursor_column = string.size() - index;

	return *this;
}

Screen & Screen::setPlace(const unsigned int row, const unsigned int column) {
	this->cursor_row = row;
	this->cursor_column = column;
	this->output << L"\033[" << row << L";" << column << L"H";
	return *this;
}
