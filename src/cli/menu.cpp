#include "menu.h"
#include "human_player.h"
#include "../lib/player/ai.h"
#include "../lib/player/ai_min_max_pruned.h"

#include <utility>
#include <array>
#include <functional>
#include <utility>

const std::wstring select_msg {L"Please, select an option: "};
const std::wstring unknown_option {L"Unknown option was given, choose a valid one"};

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

    const std::wstring msg = L"Select a number for a mode: ";
    this->screen.print(msg);
    unsigned int column = this->screen.getColumn();
    unsigned int row = this->screen.getRow();
    int mode = this->screen.getInt();
    while (mode <= 0 || mode >= static_cast<int>(MenuOption::TOTAL)) {
        this->errorMsgPrint(msg, L"Invalid number for option", row);
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
    this->playersType.clear();
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

    std::array<std::wstring, 3> options = {
        L"Player menu",
        L"Table menu",
        L"Proceed to game"
    };

    Menu::printOptions<3>(options);

    this->screen.print(select_msg);
    unsigned row = this->screen.getRow();
    int option = 0;

    do {
        option = this->screen.getInt();
        switch(option) {
            case 1:
                return this->playersMenu();
                break;
            case 2:
                return this->tableMenu();
                break;
            case 3:
                if (this->players.empty()) {
                    this->errorMsgPrint(select_msg, L"No player(s) was(were) added", row);
                    continue;
                } else if(this->table == nullptr) {
                    this->errorMsgPrint(select_msg, L"No table row and column was set", row);
                    continue;
                }
                break;
            default:
                this->errorMsgPrint(select_msg, unknown_option, row);
                continue;
                break;
        }

        break;
    } while(true);

    return *this;
}

Menu & Menu::playersMenu() {
    this->screen.clearScreen();

    std::array<std::wstring, 5> options {
        L"Add player",
        L"Change player symbol",
        L"Change player order",
        L"Delete player",
        L"Back to game menu"
    };

    Menu::printOptions<5>(options);

    this->screen.print(select_msg);
    unsigned int row = this->screen.getRow();
    int option = 0;
    while(true) {
        option = this->screen.getInt();

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
                this->errorMsgPrint(select_msg, unknown_option, row);
                continue;
        }

        break;
    }
    return *this;
}

Menu & Menu::addPlayer() {
    this->screen.clearScreen();

    std::array<std::wstring, 4> options {
        L"Human player (played by users)",
        L"AI Player (played by the computer)",
        L"AI Player with MinMax",
        L"Go back to player menu"
    };

    Menu::printOptions<4>(options);

    this->screen.print(select_msg);
    unsigned int row = this->screen.getRow();
    unsigned int column = this->screen.getColumn();
    int option = 0;

    while(true) {
        option = this->screen.getInt();
        switch(option) {
            case 1:
            case 2:
            case 3:
                break;
            case 4:
                return this->playersMenu();
                break;
            default:
                this->errorMsgPrint(select_msg, unknown_option, row);
                continue;
        }

        break;
    }

    this->screen.clearScreen();
    difficulty dif;
    if (option == 2) {
        std::array<std::wstring, 3> difficulties {
            L"Easy difficulty - Random moves",
            L"Normal difficulty - 1/2 of doing random moves or thinking",
            L"Hard difficulty - thoughtful moves"
        };
        Menu::printOptions<3>(difficulties);
        this->screen.print(select_msg);

        while (true) {
            dif = static_cast<difficulty>(this->screen.getInt()) ;
            
            if (dif > difficulty::HARD || dif < difficulty::EASY) {
                this->errorMsgPrint(select_msg, unknown_option, row);
            } else {
                break;
            }
        }
    }

    const std::wstring msg = L"Type the symbol for player: ";
    this->screen.clearScreen().print(msg);
    row = this->screen.getRow();
    column = this->screen.getColumn();
    
    do {
        std::wstring symbol = this->screen.getLine();
        if (symbol.size() != 1) {
            this->errorMsgPrint(msg, L"Number of characters for symbol needs to be 1", row);
            continue;
        }
        Player<std::wstring> * player = nullptr;
        try {
            if (option == 1) {
                player = new HumanPlayer(symbol, this->screen);
                this->playersType.emplace_back(&user);

            } else if (option == 2) {
                player = new AI<std::wstring>(symbol, dif);
                this->playersType.emplace_back(&ai);
            } else {
                player = new AIMinMaxPruned<std::wstring>(symbol);
                this->playersType.emplace_back(&aiMinMax);
            }

            this->players.emplace_back(player);
            break;
        } catch(UnusableSymbol & error) {
            this->errorMsgPrint(msg, UNUSABLE_SYMBOL_WMSG, row);
            continue;
        }
    } while(true);

    this->screen.clearScreen();
    this->printPlayers();
    this->screen.print(L"Player created with success. Enter to go back to player menu\n");
    this->screen.getLine();
    
    return this->playersMenu();
}

Menu & Menu::deletePlayer() {
    this->screen.clearScreen();

    this->printPlayers();
    if (this->players.empty()) {
        this->screen.print(L"Press enter to go back to player menu");
        this->screen.getLine();
        return this->playersMenu();
    } else {
        this->screen.setPlace(this->screen.getRow() - 1, 0).print(L"0 - go back to menu\n\n");
    }

    std::wstring msg = L"Select a player number (order) to delete: ";
    this->screen.print(msg);
    unsigned int row = this->screen.getRow();
    do {
        int option = this->screen.getInt();
        if (option == 0) {
            break;
        }

        if (option > this->players.size()) {
            this->errorMsgPrint(msg, L"Player not found at " + std::to_wstring(option), row);
            continue;
        }

        delete this->players[option - 1];
        this->players.erase(this->players.begin() + (option - 1));
        this->playersType.erase(this->playersType.begin() + (option - 1));
        this->screen.clearScreen();
        this->printPlayers();
        this->screen.print(L"Player deleted with success. Press enter to go back to player menu\n");
        this->screen.getLine();
        break;
    } while(true);

    return this->playersMenu();
}

Menu & Menu::changePlayerSymbol() {
    this->screen.clearScreen();

    this->printPlayers();
    if (this->players.empty()) {
        this->screen.print(L"Press enter to go back to player menu");
        this->screen.getLine();
        return this->playersMenu();
    } else {
        this->screen.setPlace(this->screen.getRow() - 1, 0).print(L"0 - go back to menu\n\n");
    }

    std::wstring msg = L"Select a player number (order) to change symbol: ";
    this->screen.print(msg);
    unsigned int row = this->screen.getRow();
    int option = 0;
    do {
        option = this->screen.getInt();
        if (option == 0) {
            return this->playersMenu();
        }

        if (option > this->players.size()) {
            this->errorMsgPrint(msg, L"Player not found at " + std::to_wstring(option), row);
            continue;
        }

        break;
    } while(true);

    Player<std::wstring> & player = *this->players[option - 1];
    this->screen.clearScreen();
    this->screen.print(L"Actual player symbol: " + player.getPlayerSymbol() + L"\n");
    msg = L"New player symbol: ";
    this->screen.print(msg);
    row = this->screen.getRow();
    do {
        std::wstring symbol = this->screen.getLine();
        if (symbol.size() != 1) {
            this->errorMsgPrint(msg, L"Number of characters for symbol needs to be 1", row);
            continue;
        }

        try {
            player.setPlayerSymbol(symbol);
        } catch(UnusableSymbol & _) {
            this->errorMsgPrint(msg, UNUSABLE_SYMBOL_WMSG, row);
            continue;
        }

        break;
    } while(true);

    this->screen.clearScreen();
    this->printPlayers();
    this->screen.print(L"Player symbol changed with success. Press enter to go back to player menu\n");
    this->screen.getLine();

    return this->playersMenu();
}

Menu & Menu::changePlayerOrder() {
    this->screen.clearScreen();

    this->printPlayers();

    if (this->players.empty()) {
        this->screen.print(L"Press enter to go back to player menu");
        this->screen.getLine();
        return this->playersMenu();
    } else {
        this->screen.setPlace(this->screen.getRow() - 1, 0).print(L"0 - go back to menu\n\n");
    }

    std::wstring msg = L"Select a player number (order) to change player order: ";
    this->screen.print(msg);
    unsigned int row = this->screen.getRow();
    int option = 0;    
    do {
        option = this->screen.getInt();
        if (option == 0) {
            return this->playersMenu();
        }

        if (option > this->players.size()) {
            this->errorMsgPrint(msg, L"Player not found at " + std::to_wstring(option), row);
            continue;
        }

        break;
    } while(true);

    // Pick the other player to exchange place.
    this->screen.clearScreen();
    this->printPlayers();
    this->screen.setPlace(this->screen.getRow() - 1, 0).print(L"-1 - go back to menu\n\n");

    msg = L"Select a player number (order) to change player order: ";
    this->screen.print(msg);
    row = this->screen.getRow();
    int option_2 = 0;    
    do {
        option_2 = this->screen.getInt();
        if (option_2 == -1) {
            break;
        }

        if (option_2 > this->players.size() || option_2 == 0) {
            this->errorMsgPrint(msg, L"Player not found at " + std::to_wstring(option_2), row);
            continue;
        }

        break;
    } while(true);

    if (option_2 != option) {
        std::swap(this->players[option -1], this->players[option_2 - 1]);
        std::swap(this->playersType[option -1], this->playersType[option_2 - 1]);
    }

    this->screen.clearScreen();
    this->printPlayers();
    this->screen.print(L"Order ").print(option).print(L" changed to ").print(option_2).print(L" with success. Press enter to go back to player menu");
    this->screen.getLine();
    return this->playersMenu();
}

Menu & Menu::tableMenu() {
    this->screen.clearScreen();
    std::array<std::wstring, 3> options = {
        L"Set row and column number",
        L"Preview table",
        L"Go back to game menu"
    };

    printOptions<3>(options);

    
    this->screen.print(select_msg);
    unsigned int row = this->screen.getRow();
    int option = 0;
    do {
        option = this->screen.getInt();

        switch(option) {
            case 1: 
                return this->setTableColumnAndRow();
            case 2:
                return this->showTablePreview();
            case 3:
                return this->customizationMenu();
            default:
                this->errorMsgPrint(select_msg, unknown_option, row);
                continue;
        }

        break;
    } while(true);

    return *this;
}

void Menu::printPlayers() {
    if (this->players.empty()) {
        this->screen.print(L"No players added yet.\n\n");
    } else {
        this->screen.print(L"Players (order - symbol - type)\n");
        for (int i = 0; i < this->players.size(); ++i) {
            std::wstring playerType = L"";
            switch (*this->playersType[i]) {
                case PlayerType::USER:
                    playerType = L"User";
                    break;
                case PlayerType::AI:
                    playerType = L"AI";
                    break;
                case PlayerType::AIMinMax:
                    playerType = L"AIMinMax";
                    break;
                default:
                    playerType = L"Unknown";
                    break;
            }
            this->screen.print(i + 1).print(L" - " + this->players[i]->getPlayerSymbol() + L" - " + playerType + L"\n");
        }
        this->screen.print(L"\n");
    }
}

template<size_t t>
void Menu::printOptions(std::array<std::wstring, t> & options) {
    for (int i = 0; i < options.size(); ++i) {
        this->screen.print(i + 1).print(L" - " + options[i] + L"\n");
    }
    this->screen.print(L"\n");
}

void Menu::errorMsgPrint(const std::wstring & entry_msg, const std::wstring error_msg, const unsigned int & row) {
    this->screen.setPlace(row + 3, 0).clearLine().print(error_msg);
    this->screen.setPlace(row, 0).clearLine().print(entry_msg);
}

Menu & Menu::setTableColumnAndRow() {
   std::wstring msg = L"Type the number of rows and columns for the table: ";
    this->screen.clearScreen().print(msg);
    int row = this->screen.getRow();
    int number_of_rows_col = 0;
    bool negative = false;
    do {
        number_of_rows_col = this->screen.getInt();
        if (number_of_rows_col <= 0) {
            this->errorMsgPrint(msg, L"Table can't have 0 or less columns and rows", row);
            negative = true;
        } else if (number_of_rows_col > 255){
            this->errorMsgPrint(msg, L"Table can't have 256 or more columns and rows", row);
            negative = true;
        } else {
            negative = false;
        }
    } while(negative);

    if (this->table != nullptr) {
        StringTable * delete_pointer = &(*this->table);
        this->table = nullptr;
        delete delete_pointer;
    }

    this->table = new StringTable(number_of_rows_col, number_of_rows_col);
    this->screen.clearScreen().print(L"Number of rows and columns was set to ").print(this->table->getColumnsNum()).print(L" with success");
    this->screen.print(L"\nPress enter to go back to table menu\n").getLine();
    return this->tableMenu();
}

Menu & Menu::showTablePreview() {
    this->screen.clearScreen();

    if (this->table == nullptr) {
        this->screen.print(L"Table row and column wasn't set yet");
        this->screen.print(L"\n\nPress enter to go back to table menu\n").getLine();

        return this->tableMenu();
    }

    this->screen.print(this->table->tableString());
    this->screen.print(L"\n Press enter to go back to table menu\n").getLine();
    return this->tableMenu();
}

Menu & Menu::clearScreenEndGame() {
    this->screen.print(L"\n\nPress enter to go to menu.");
    this->screen.getLine();
    return *this;
}

MenuFinishOption Menu::playAgain() {
    this->screen.clearScreen();

    std::array<std::wstring, 3> options {
        L"Play again",
        L"Modify options",
        L"Exit"
    };

    this->printOptions(options);
    this->screen.print(select_msg);
    unsigned int row = this->screen.getRow();

    do {
        int option = this->screen.getInt();

        switch(option) {
            case 1:
                return MenuFinishOption::PLAY_AGAIN;
                break;
            case 2:
                return MenuFinishOption::MODIFY_GAME;
                break;
            case 3:
                return MenuFinishOption::EXIT;
                break;
            default:
                this->errorMsgPrint(select_msg, unknown_option, row);
                continue;
                break;
        }
    } while(true);
}