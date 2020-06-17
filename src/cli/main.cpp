#include <string>
#include <iostream>
#include <locale>

#include "cli_tic_tac_toe.h"
#include "../lib/player/ai.h"
#include "human_player.h"
#include "string_table.h"
#include "screen.h"

using namespace tic_tac_toe;
int main(int argc, char ** argv) {
    // Define the locale so that wide characters are interpreted as UTF-8
    std::setlocale(LC_ALL, "");

    Screen screen(std::wcin, std::wcout);
    auto * player_1 = new AI<std::wstring>{L"X"};
    auto * player_2 = new HumanPlayer{L"O", screen};
    auto table = new StringTable{3, 3};
    CliTicTacToe game(screen, {player_1, player_2}, table);

    GameStatus status;
    do {
        screen.clearScreen();
        //setPlace(1, 1);
        status = game.showBoard().playerPlay().isThereAWinner();
    } while(status == GameStatus::ONGOING);

    screen.clearScreen();
    game.showBoard();
    switch (status) {
        case GameStatus::DRAW:
            std::wcout << L"Nobody won!";
            break;
        case GameStatus::WIN:
            std::wcout << L"Player " << game.getWinner()->getPlayerSymbol() << " won!";
            break;
        case GameStatus::ONGOING:
        default:
            break;
    }

    return 0;
}
