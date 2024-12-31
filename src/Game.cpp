//
// Created by Daniel Skalski on 28/12/2024.
//

#include <Game.h>

Game::Game(char mode, int difficulty)
    : sudoku(Sudoku(static_cast<Sudoku::Mode>(mode), static_cast<Sudoku::Difficulty>(difficulty))),
      interface(Interface::getInstance()) {}

void Game::start() {
    if (sudoku.mode == Sudoku::USER) {
        playUserMode();
    } else if (sudoku.mode == Sudoku::SOLVER) {
        playSolverMode();
    } else {
        throw std::runtime_error("Unknown mode in sudoku!\n");
    }

}

void Game::playSolverMode() {
    interface.displayInputAndSolveInfo();
    Board givenBoard = dynamic_cast<Solver*>(sudoku.player.get())->inputBoardToComplete();
    auto solution = dynamic_cast<Solver*>(sudoku.player.get())->solve(givenBoard);
    if (!solution.first) {
        interface.displayMessage("The board is not solvable\n", Interface::RED);
        return;
    }
    sudoku.board = solution.second;
    dynamic_cast<Solver*>(sudoku.player.get())->solvedBoard = solution.second;

    std::cout << "\nChoose an option:\n";
    std::cout << "1. Complete step by step\n";
    std::cout << "2. Complete all at once\n";

    int modeChoice = interface.getUserInputInt({1, 2});
    switch (modeChoice) {
        case 1: {
            while (!sudoku.board.isSolved()) {
                auto move = sudoku.player->takeTurn();
                sudoku.board.currentState[move.first.first][move.first.second] = move.second;
                interface.displayBoard(sudoku.board);
                std::cout << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        } break;
        case 2: {
            interface.displayBoard(sudoku.board);
        } break;
        default: {
            throw std::runtime_error("Unknown solver type!\n");
        }
    }
}

void Game::playUserMode() {
    Database& db = Database::getInstance();
    while (!sudoku.board.isSolved()) {
        interface.displayBoard(sudoku.board);
        interface.displayInGameOptions(sudoku.manager.errorTracker.currentErrors, sudoku.manager.errorTracker.maxErrors);

        int userChoice = interface.getUserInputInt({1, 2, 3});
        switch (userChoice) {
            case 1: {
                auto move = sudoku.player->takeTurn();
                if (sudoku.manager.errorTracker.validateMove(sudoku.board, move)) {
                    sudoku.board.currentState[move.first.first][move.first.second] = move.second;
                } else {
                    interface.displayMessage("Invalid move!\n", Interface::RED);
                }
                if (sudoku.manager.errorTracker.currentErrors > sudoku.manager.errorTracker.maxErrors) {
                    interface.displayMessage("Game over! Maximum errors exceeded", Interface::RED);
                    return;
                }

            } break;
            case 2: {
                sudoku.manager.hinter.provideHint(sudoku.board);
            } break;
            case 3: {
                db.saveCurrentState(sudoku.board, sudoku.boardID, sudoku.difficulty, sudoku.manager.errorTracker.currentErrors);
                std::cout << "Hope to see you soon!\n";
                exit(0);
            }
            default:
                throw std::runtime_error("Unknown user choice in Game::playUserMode\n");
        }
    }
    interface.displayMessage("Congratulations! You have solved the board.", Interface::GREEN);
    if (db.updateBestScore(sudoku.manager.timer.getElapsedTime())) {
        interface.displayMessage("You have new best score!", Interface::GREEN);
    }
    db.clearCurrentState();
}
