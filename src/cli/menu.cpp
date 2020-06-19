#include "menu.h"
#include <utility>

Menu::Menu(Screen & screen) : screen(screen) {}

MenuOption Menu::askForMode() {
    this->screen.clearScreen();

    std::pair<MenuOption, std::wstring> default_mode(
        MenuOption::DEFAULT, L"default mode (1 player and 1 AI at normal dif)"
        );
    std::pair<MenuOption, std::wstring> customized_mode(
        MenuOption::CUSTOMIZED, L"customized mode (decide how many will play and size of the table)"
        );


    this->screen.print(static_cast<int>(default_mode.first)).print(L" - ").print(default_mode.second).print(L"\n");
    this->screen.print(static_cast<int>(customized_mode.first)).print(L" - ").print(customized_mode.second).print(L"\n");

    this->screen.print(L"Select a number for a mode: ");
    unsigned int column = this->screen.getColumn();
    unsigned int row = this->screen.getRow();
    int mode = this->screen.getInt();
    while (mode < 0 || mode >= static_cast<int>(MenuOption::TOTAL)) {
        this->screen.print(L"\n\n").clearLine().print(L"Invalid number for option");
        this->screen.setPlace(row, column).clearLine().print(L"Select a number for a mode: ");
        mode = this->screen.getInt();
    }

    return static_cast<MenuOption>(mode);
}