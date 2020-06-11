#include <string>
#include "cli_tic_tac_toe.h"
#include "../lib/player/ai.h"
#include "string_table.h"
#include "utils.h"
#include <iostream>
#include <locale>

//using namespace tic_tac_toe;
int main(int argc, char ** argv) {
    // Define the locale so that wide characters are interpreted as UTF-8
    std::setlocale(LC_ALL, "");

    auto * player_1 = new AI<std::wstring>{L"X"};
    auto * player_2 = new AI<std::wstring>{L"O"};
    auto table = new StringTable{3, 3};
    CliTicTacToe game({player_1, player_2}, table);

    GameStatus status;
    do {
        //clearScreen();
        //setPlace(1, 1);
        game.showBoard();
        game.playerPlay();
        status = game.isThereAWinner();
    } while(status == GameStatus::ONGOING);

    game.showBoard();
    switch (status) {
        case GameStatus::DRAW:
            std::wcout << L"Nobody won!";
            break;
        case GameStatus::WIN:
            std::wcout << L"Player won!";
            break;
    }

    return 0;
}
