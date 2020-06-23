#include <string>
#include <iostream>
#include <locale>

#include "cli_tic_tac_toe.h"
#include "menu.h"
#include "../lib/player/ai.h"
#include "human_player.h"
#include "string_table.h"
#include "screen.h"

using namespace tic_tac_toe;
int main(int argc, char ** argv) {
    // Define the locale so that wide characters are interpreted as UTF-8
    std::setlocale(LC_ALL, "");
    
    Screen screen(std::wcin, std::wcout);
    Menu menu(screen);

    MenuOption option = menu.askForMode();

    CliTicTacToe * game = nullptr;
    switch(option) {
        case MenuOption::DEFAULT:
        case MenuOption::TOTAL:
        default: {
            auto * player_1 = new HumanPlayer{L"X", screen};
            auto * player_2 = new AI<std::wstring>{L"O"};
            auto * table = new StringTable{3, 3};
            game = new CliTicTacToe(screen, {player_1, player_2}, table);
            break;
        }
        case MenuOption::CUSTOMIZED: {
            menu.customizationMenu();
            std::vector<Player<std::wstring> *> players = menu.getPlayers();
            StringTable * table = menu.getTable();
            game = new CliTicTacToe(screen, players, table);
            break;
        }
    }

    GameStatus status;
    do {
        screen.clearScreen();
        status = game->showBoard().playerPlay().isThereAWinner();
    } while(status == GameStatus::ONGOING);

    screen.clearScreen();
    game->showBoard();
    switch (status) {
        case GameStatus::DRAW:
            std::wcout << L"Nobody won!";
            break;
        case GameStatus::WIN:
            std::wcout << L"Player " << game->getWinner()->getPlayerSymbol() << " won!";
            break;
        case GameStatus::ONGOING:
        default:
            break;
    }

    return 0;
}
