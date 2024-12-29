//
// Created by Daniel Skalski on 28/12/2024.
//

#include "Game.h"

Game::Game(char mode, int difficulty)
    : sudoku(Sudoku(static_cast<Sudoku::Mode>(mode), static_cast<Sudoku::Difficulty>(difficulty), database.savedBoards)),
    interface(Interface()),
    database(Database()){
    database.loadBoards();
    database.loadSavedState();
}

void Game::start() {
    interface.displayMainMenu(database.bestScore);
    char choice;
    std::cin >> choice;
    switch (choice) {
        case '1':
            sudoku.chooseBoard(database.savedBoards);
            break;
        case '2':
            return;

    }
    interface.displayBoard(sudoku.board);
}
