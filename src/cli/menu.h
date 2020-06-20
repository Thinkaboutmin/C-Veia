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
    std::vector<Player<std::wstring> *> players;
    StringTable * table = nullptr;

public:
    Menu(Screen & screen);

    /*
    * Ask for the mode which the game will be played.
    * 
    * It will return a default or customized or any other added.
    */
    MenuOption askForMode();

    /*
    * Ask for the user to type the customization of their game.
    */
    Menu & customizationMenu();

    /*
    * Return the players chosen by the user and delete it from the class.
    */
    std::vector<Player<std::wstring> *> getPlayers();

    /*
    * Return the table created by the user and delte it from the class.
    */
    StringTable * getTable();
    
private:

    Menu & playersMenu();

    Menu & addPlayer();

    Menu & deletePlayer();

    Menu & changePlayerSymbol();

    Menu & changePlayerOrder();

    Menu & tableMenu();

    void printPlayers();

    void unknownOptionMsg(const unsigned int & row);
};

#endif