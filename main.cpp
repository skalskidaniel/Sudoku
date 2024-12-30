#include <game.h>
#include <iostream>

int getUserInput(const std::vector<int> &availableValues) {
    // returns input from user with error handling
    int userChoice;
    while (true) {
        std::cin >> userChoice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please choose valid option." << std::endl;
        } else if (std::find(availableValues.begin(), availableValues.end(), userChoice) == availableValues.end()) {
            std::cout << "Invalid input! Please choose valid option." << std::endl;
        } else {
            // input is valid
            return userChoice;
        }
    }
}

bool newGameMenu(Database &startDatabase) {
    // returns false if user wants to quit the game
    Interface startInterface = Interface();
    startInterface.displayMainMenu(startDatabase.bestScore);
    // 1. new game 2. quit
    int choice = getUserInput({1, 2});
    switch (choice) {
        case 1: {
            startInterface.displayModeSelection();
            // 1. user mode 2. solver mode
            int mode = getUserInput({1, 2});
            switch (mode) {
                case 1: {
                    startInterface.displayDifficultySelection();
                    int difficulty = getUserInput({1, 2, 3});
                    Game game = Game('U', difficulty);
                    game.start();
                    return true;
                }
                case 2: {
                    Game game = Game('S', 1);
                    game.start();
                    return true;
                }
                default: {
                    throw std::runtime_error("Unknown game mode in newGameMenu()!\n");
                }
            }
        }
        case 2: {
            std::cout << "Hope to see you soon!\n";
            return false;
        }
        default: {
            throw std::runtime_error("Unknown user choice in newGameMenu()!\n");
        }
    }
}

bool resumeMenu(Database &startDatabase) {
    // returns false if user wants to quit the game
    Interface startInterface = Interface();
    startInterface.displayResumeMenu();
    // 1. Resume 2. new game 3. quit
    int choice = getUserInput({1, 2, 3});
    switch (choice) {
        case 1: {
            // TODO make sure it resumes the game
            Game game = Game('U', startDatabase.difficulty);
            game.start();
            return true;
        }
        case 2: {
            return newGameMenu(startDatabase);
        }
        case 3: {
            std::cout << "Hope to see you soon!\n";
            return false;
        }
        default: {
            throw std::runtime_error("Unknown user choice in resumeMenu()!\n");
        }
    }
}



bool mainMenu() {
    // returns false if user wants to quit the game
    Database startDatabase(false);
    if (startDatabase.canBeResumed) {
        return resumeMenu(startDatabase);
    } else {
        return newGameMenu(startDatabase);
    }
}


int main() {
    while (mainMenu());
}
