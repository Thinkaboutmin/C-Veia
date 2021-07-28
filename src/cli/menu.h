#ifndef TICTACTOE_MENU_H
#define TICTACTOE_MENU_H

#include <string>
#include <vector>
#include <array>
#include <map>

#include "../lib/player/player.h"
#include "menu_enum.h"
#include "screen.h"
#include "string_table.h"
#include "player_type.h"


using namespace tic_tac_toe;
class Menu {
private:
    static constexpr PlayerType user = PlayerType::USER;
    static constexpr PlayerType ai = PlayerType::AI;

    static constexpr PlayerType aiMinMax = PlayerType::AIMinMax;

    std::vector<Player<std::wstring> *> players;

    std::vector<const PlayerType *> playersType;

    Screen & screen;

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

    /*
    * Ask the user if it wants to play again.
    */
    MenuFinishOption playAgain();

    Menu & clearScreenEndGame();
    
private:

    /*
    * The player menu composed of:
    * Add player
    * Delete player
    * Change player symbol
    * Change player order
    * Back to main menu.
    */
    Menu & playersMenu();

    /*
    * Add a player according to what the user desired.
    */
    Menu & addPlayer();

    /*
    * Delete a chosen player.
    */
    Menu & deletePlayer();

    /*
    * Change a player symbol.
    */
    Menu & changePlayerSymbol();

    /*
    * Change the player order.
    */
    Menu & changePlayerOrder();

    Menu & tableMenu();

    Menu & setTableColumnAndRow();

    Menu & showTablePreview();

    void printPlayers();

    /*
    * Prints an error in a default way.
    * entry_msg -> Message which got the input from.
    * error_msg -> Message to display below
    * row -> Row of where the entry_msg was displayed.
    */
    void errorMsgPrint(const std::wstring & entry_msg, const std::wstring error_msg, const unsigned int & row);

    /*
    * Print an array in a default way.
    */
    template<size_t t>
    void printOptions(std::array<std::wstring, t> & options);
};

#endif