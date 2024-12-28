//
// Created by Daniel Skalski on 28/12/2024.
//

#include "Interface.h"
#include <iostream>

void Interface::displayMainMenu(const int &bestScore) {
    std::cout << "Welcome to Sudoku game\n";
    std::cout << "Your best score so far: " << bestScore << std::endl;
    std::cout << "Choose an option:\n";
    std::cout << "1. Start a game\n";
    std::cout << "2. Quit\n";
}

void Interface::displayResumeMenu() {
    std::cout << "Welcome to Sudoku game\n";
    std::cout << "It seems like you haven't finished your last game, do you want to resume?\n";
    std::cout << "Choose an option:\n";
    std::cout << "1. Resume recent game\n";
    std::cout << "2. Start a new game (all progress made will be lost)\n";
    std::cout << "3. Quit\n";
}

void Interface::displayModeSelection() {
    std::cout << "The game has two modes:\n";
    std::cout << "1. Solve it (you will have to complete sudoku)\n";
    std::cout << "2. Input & solve (solver will complete your board)\n";
    std::cout << "Which game mode do you choose?\n";
}

void Interface::displayDifficultySelection() {
    std::cout << "Choose desired difficulty:\n";
    std::cout << "1. Easy\n";
    std::cout << "2. Medium\n";
    std::cout << "3. Hard\n";
}

void Interface::displayBoard(const Board &b) {
    // TODO
    // inserted digits should be green
    std::cout << "\t1\t2\t3\t4\t5\t6\t7\t8\t9\n";
    const char rowLabels[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    for (int i = 0; i < 9; ++i) {
        std::cout << rowLabels[i] << '\t';
        for (int j = 0; j < 9; ++j) {
            if (b.currentState[i][j] == '0') {
                std::cout << "_\t";
            } else {
                std::cout << b.currentState[i][j] << "\t";
            }
        }
        std::cout << "\n";
    }

}

void Interface::displayInGameOptions(const int &currentErorrs, const int &maxErrors) {
    std::cout << "Errors made in current game (limit = " << maxErrors << "): " << currentErorrs << std::endl;
    std::cout << "Choose an option:\n";
    std::cout << "2. Undo previous turn\n";
    std::cout << "3. Take a hint\n";
    std::cout << "4. Quit a game\n";
}


void Interface::displayInputAndSolveInfo() {
    std::cout << "Please input your own sudoku board.\n";
    std::cout << "You will have to write each line one by one.\n";
    std::cout << "Places with missing digit mark as '0'.\n";
    std::cout << "Solver will check whether it is solvable, and solve if it is so.\n";
}

void Interface::sound() {
    // TODO
}

void Interface::displayMessage(const std::string &message) {
    std::cout << message << std::endl;
    // TODO
    // add colours to the message
}


