#ifndef TICTACTOE_MENU_H
#define TICTACTOE_MENU_H

#include <string>
#include <vector>

#include "../lib/player/player.h"
#include "menu_enum.h"
#include "screen.h"
#include "string_table.h"


using namespace tic_tac_toe;
class Menu {
private:
    Screen & screen;
public:

    Menu(Screen & screen);

    MenuOption askForMode();

    std::vector<Player<std::wstring> *> askForPlayers();

    StringTable askForTable();

    const std::vector<Player<std::wstring> *> defaultPlayers();
};

#endif