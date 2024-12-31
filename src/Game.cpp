//
// Created by Daniel Skalski on 28/12/2024.
//

#include "Game.h"
#include <Solver.h>
#include <User.h>
#include <thread>
#include <iostream>


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
    if (!dynamic_cast<Solver*>(sudoku.player.get())->isSolvable(givenBoard)) {
        std::cout << "The board is not solvable.\n";
        return;
    }
    std::cout << "\nChoose an option:\n";
    std::cout << "1. Complete step by step\n";
    std::cout << "2. Complete all at once\n";

    int modeChoice = interface.getUserInputInt({1, 2});
    // 1. Step by step 2. all at once
    switch (modeChoice) {
        case 1: {
            while (!dynamic_cast<Solver*>(sudoku.player.get())->is_solved) {
                auto move = sudoku.player->takeTurn();
                sudoku.board.currentState[move.first.first][move.first.second] = move.second;
                interface.displayBoard(sudoku.board);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        } break;
        case 2: {
            sudoku.board = dynamic_cast<Solver*>(sudoku.player.get())->solve(givenBoard);
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

        int userChoice = interface.getUserInputInt({1, 2, 3, 4});
        // 1. insert a digit 2. undo 3. hint 4. quit and save
        switch (userChoice) {
            case 1: {
                auto move = sudoku.player->takeTurn();
                if (sudoku.manager.errorTracker.validateMove(sudoku.board, move)) {
                    sudoku.board.currentState[move.first.first][move.first.second] = move.second;
                    sudoku.manager.history.update(sudoku.board);
                } else {
                    interface.displayMessage("Invalid move!\n", Interface::RED);
                }
                if (sudoku.manager.errorTracker.currentErrors > sudoku.manager.errorTracker.maxErrors) {
                    interface.displayMessage("Game over! Maximum errors exceeded", Interface::RED);
                    return;
                }

            } break;
            case 2: {
                if (sudoku.manager.history.canUndo()) {
                    sudoku.board = sudoku.manager.history.undo(sudoku.board);
                } else {
                    interface.displayMessage("No more steps to undo\n", Interface::RED);
                }
            } break;
            case 3: {
                sudoku.manager.hinter.provideHint(sudoku.board);
                sudoku.manager.history.update(sudoku.board);
            } break;
            case 4: {
                db.saveCurrentState(sudoku.board, sudoku.boardID, sudoku.difficulty, sudoku.manager.errorTracker.currentErrors);
                std::cout << "Hope to see you soon!\n";
                exit(0);
            }
            default:
                throw std::runtime_error("Unknown user choice in Game::playUserMode\n");
        }
    }
    // sudoku is solved now
    interface.displayMessage("Congratulations! You have solved the board.", Interface::GREEN);
    if (db.updateBestScore(sudoku.manager.timer.getElapsedTime())) {
        interface.displayMessage("You have new best score!", Interface::GREEN);
    }
    db.clearCurrentState();
}
