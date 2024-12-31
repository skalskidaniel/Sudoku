//
// Created by Daniel Skalski on 28/12/2024.
//

#include <Interface.h>

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

void Interface::displayBoard(Board &b) {
    std::cout << "\t\033[1m1\t2\t3\t4\t5\t6\t7\t8\t9\033[0m\n";
    const char rowLabels[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    for (int i = 0; i < 9; ++i) {
        std::cout << "\033[1m" << rowLabels[i] << "\033[0m\t";
        for (int j = 0; j < 9; ++j) {
            if (b.currentState[i][j] == '0') {
                std::cout << "_\t";
            } else {
                if (b.isInsertedByUser(i, j)) {
                    std::cout << "\033[1;32m" << b.currentState[i][j] << "\033[0m\t";
                } else {
                    std::cout << b.currentState[i][j] << "\t";
                }
            }
        }
        std::cout << "\n";
    }
}

void Interface::displayInGameOptions(const int &currentErrors, const int &maxErrors) {
    std::cout << "Errors made in current game (limit = " << maxErrors << "): " << currentErrors << std::endl;
    std::cout << "Choose an option:\n";
    std::cout << "1. Insert a digit\n";
    std::cout << "2. Take a hint\n";
    std::cout << "3. Quit a game (progress will be saved)\n";
}


void Interface::displayInputAndSolveInfo() {
    std::cout << "Please input your own sudoku board.\n";
    std::cout << "You will have to write each line one by one.\n";
    std::cout << "Places with missing digit mark as '0'.\n";
    std::cout << "Solver will check whether it is solvable, and solve if it is so.\n";
}

void Interface::displayMessage(const std::string &message, const Colour &c) {
    std::string colorCode;
    switch (c) {
        case GREEN:
            colorCode = "\033[1;32m";
        break;
        case YELLOW:
            colorCode = "\033[1;33m";
        break;
        case RED:
            colorCode = "\033[1;31m";
        break;
    }
    std::cout << colorCode << message << "\033[0m" << std::endl;
}


int Interface::getUserInputInt(const std::vector<int> &availableValues) {
    int userChoice;
    while (true) {
        std::cin >> userChoice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayMessage("Invalid input! Please choose valid option.", RED);
        } else if (std::find(availableValues.begin(), availableValues.end(), userChoice) == availableValues.end()) {
            displayMessage("Invalid input! Please choose valid option.", RED);
        } else {
            return userChoice;
        }
    }
}

char Interface::getUserInputChar(const std::vector<char> &availableValues) {
    char userChoice;
    while (true) {
        std::cin >> userChoice;
        userChoice = std::toupper(userChoice);

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            displayMessage("Invalid input! Please choose valid option.", RED);
        } else if (std::find(availableValues.begin(), availableValues.end(), userChoice) == availableValues.end()) {
            displayMessage("Invalid input! Please choose valid option.", RED);
        } else {
            return userChoice;
        }
    }
}