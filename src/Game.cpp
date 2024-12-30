//
// Created by Daniel Skalski on 28/12/2024.
//

#include "Game.h"

#include <Solver.h>
#include <User.h>
#include <thread>

Game::Game(char mode, int difficulty)
    : database(Database()),
    sudoku(Sudoku(static_cast<Sudoku::Mode>(mode), static_cast<Sudoku::Difficulty>(difficulty), database.savedBoards)),
    interface(Interface()) {}

void Game::start() {
    if (sudoku.mode == 'U') {
        sudoku.chooseBoard(database.savedBoards);
        playUserMode();
    } else if (sudoku.mode == 'S') {
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
    int modeChoice;
    while (true) {
        std::cin >> modeChoice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please choose valid option." << std::endl;
        } else if (modeChoice != 1 && modeChoice != 2) {
            std::cout << "Invalid input! Please choose valid option." << std::endl;
        } else {
            break;
        }
    }

    if (modeChoice == 1) {
        while (!dynamic_cast<Solver*>(sudoku.player.get())->is_solved) {
            auto move = sudoku.player->takeTurn();
            sudoku.board.currentState[move.first.first][move.first.second] = move.second;
            interface.displayBoard(sudoku.board);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } else if (modeChoice == 2) {
        sudoku.board = dynamic_cast<Solver*>(sudoku.player.get())->solve(givenBoard);
        interface.displayBoard(sudoku.board);
    } else {
        throw std::runtime_error("Unknown solver type!\n");
    }
}

void Game::playUserMode() {
    while (!sudoku.board.isSolved()) {
        interface.displayBoard(sudoku.board);
        interface.displayInGameOptions(sudoku.manager.errorTracker.currentErrors, sudoku.manager.errorTracker.maxErrors);

        int userChoice;

        while (true) {
            std::cin >> userChoice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please choose a valid option." << std::endl;
            } else if (userChoice < 1 || userChoice > 4) {
                std::cout << "Invalid input! Please choose a valid option." << std::endl;
            } else {
                break;
            }
        }

        if (userChoice == 1) {
            // insert a digit
            auto move = sudoku.player->takeTurn();
            // TODO change errorTracker.validateMove() to accept output from function above, and check if it is valid inside it. it should return true or false if it is valid and increment erorr count
            if (sudoku.manager.errorTracker.validateMove( sudoku.board ,move)) {
                sudoku.board.currentState[move.first.first][move.first.second] = move.second;
            }
            if (sudoku.manager.errorTracker.currentErrors > sudoku.manager.errorTracker.maxErrors) {
                interface.displayMessage("Game over! Maximum errors exceeded", Interface::RED);
                return;
            }

        } else if (userChoice == 2) {
            // undo
            sudoku.manager.history.undo(sudoku.board);
        } else if (userChoice == 3) {
            // hint
            sudoku.manager.hinter.provideHint(sudoku.board);
        } else if (userChoice == 4) {
            // quit and save
            database.saveCurrentState(sudoku.board, sudoku.boardID);
            std::cout << "Hope to see you soon!\n";
            exit(0);
        } else {
            throw std::runtime_error("Unknown user choice in Game::playUserMode\n");
        }
    }
    // sudoku is solved now
    interface.displayMessage("Congratulations! You have solved the board.", Interface::GREEN);
    // TODO update best score based on timer
    return;
}
