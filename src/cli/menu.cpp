#include "menu.h"
#include <utility>
#include <array>
#include <functional>
#include <utility>

const std::wstring select_msg {L"Please, select an option: "};

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
    while (mode <= 0 || mode >= static_cast<int>(MenuOption::TOTAL)) {
        this->screen.print(L"\n\n").clearLine().print(L"Invalid number for option");
        // Can't know how many characters were given by the user hence we clear the entire line.
        this->screen.setPlace(row, column).clearLine().print(L"Select a number for a mode: ");
        mode = this->screen.getInt();
    }

    return static_cast<MenuOption>(mode);
}

std::vector<Player<std::wstring> *> Menu::getPlayers() {
    if (this->players.empty()) {
        return players;
    }

    auto tmp_players = this->players;
    this->players.clear();
    return tmp_players;
}

StringTable * Menu::getTable() {
    if (this->table == nullptr) {
        return nullptr;
    }

    StringTable * tmp_table = this->table;
    this->table = nullptr;
    return tmp_table;
}

Menu & Menu::customizationMenu() {
    this->screen.clearScreen();

    std::array<std::wstring, 2> options = {
        L"Player menu",
        L"Table menu"
        L"Proceed to game"
    };

    for (int i = 0; i < options.size(); ++i) {
        this->screen.print(i + 1).print(L" - " + options[i] + L"\n");
    }

    this->screen.print(select_msg);
    unsigned row = this->screen.getRow();
    int desired_option = this->screen.getInt();

    while(true) {
        switch(desired_option) {
            case 1:
                return this->playersMenu();
                break;
            case 2:
                return this->tableMenu();
                break;
            case 3:
                if (this->players.empty()) {
                    this->screen.setPlace(this->screen.getRow() + 2, 0).clearLine();
                    this->screen.print(L"No player(s) was(were) added.");
                    this->screen.setPlace(row, 0).clearLine().print(select_msg);
                    desired_option = this->screen.getInt();
                    continue;
                } else if(this->table == nullptr) {
                    this->screen.setPlace(this->screen.getRow() + 2, 0).clearLine();
                    this->screen.print(L"No player(s) was(were) added.");
                    this->screen.setPlace(row, 0).clearLine().print(select_msg);
                    desired_option = this->screen.getInt();
                    continue;
                }
                break;
            default:
                this->unknownOptionMsg(row);
                desired_option = this->screen.getInt();
                continue;
                break;
        }
    }

    return *this;
}

Menu & Menu::playersMenu() {
    std::array<std::wstring, 5> options {
        L"Add player",
        L"Change player symbol",
        L"Change player order",
        L"Delete player",
        L"Back to game menu"
    };

    for (int i = 0; i < options.size(); ++i) {
        this->screen.print(i + 1).print(L" - " + options[i] + L"\n");
    }

    this->screen.print(select_msg);
    unsigned int row = this->screen.getRow();
    int option = this->screen.getInt();
    while(true) {
        switch(option) {
            case 1:
                return this->addPlayer();
                break;
            case 2:
                return this->changePlayerSymbol();
                break;
            case 3:
                return this->changePlayerOrder();
                break;
            case 4:
                return this->deletePlayer();
                break;
            case 5:
                return this->customizationMenu();
                break;
            default:
                this->unknownOptionMsg(row);
                option = this->screen.getInt();
                continue;
        }
    }
    return *this;
}

Menu & Menu::addPlayer() {
    this->screen.clearScreen();
    this->printPlayers();


    
    return *this;
}

Menu & Menu::deletePlayer() {
    this->screen.clearScreen();
    this->printPlayers();

    return *this;
}

Menu & Menu::changePlayerSymbol() {
    this->screen.clearScreen();
    this->printPlayers();

    return *this;
}

Menu & Menu::changePlayerOrder() {
    this->screen.clearScreen();
    this->printPlayers();

    return *this;
}

Menu & Menu::tableMenu() {
    this->screen.clearScreen();
    this->printPlayers();

    return *this;
}

void Menu::unknownOptionMsg(const unsigned int & row) {
    this->screen.setPlace(this->screen.getRow() + 2, 0).clearLine();
    this->screen.print(L"Unknown option.");
    this->screen.setPlace(row, 0).clearLine().print(select_msg);
}

void Menu::printPlayers() {
    if (this->players.empty()) {
        this->screen.print(L"No players added yet.\n\n");
    } else {
        this->screen.print(L"Players (order - symbol)\n");
        for (int i = 0; i < this->players.size(); ++i) {
            this->screen.print(i + 1).print(L" - " + this->players[i]->getPlayerSymbol() + L"\n");
        }
        this->screen.print(L"\n");
    }
}