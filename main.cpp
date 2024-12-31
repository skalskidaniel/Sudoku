#include <game.h>
#include <iostream>

bool newGameMenu(Database &startDatabase) {
    // returns false if user wants to quit the game
    Interface& interface = Interface::getInstance();
    interface.displayMainMenu(startDatabase.bestScore);
    // 1. new game 2. quit
    int choice = interface.getUserInput({1, 2});
    switch (choice) {
        case 1: {
            interface.displayModeSelection();
            // 1. user mode 2. solver mode
            int mode = interface.getUserInput({1, 2});
            switch (mode) {
                case 1: {
                    interface.displayDifficultySelection();
                    int difficulty = interface.getUserInput({1, 2, 3});
                    Game game('U', difficulty);
                    game.start();
                    return true;
                }
                case 2: {
                    Game game('S', 1);
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
    Interface& interface = Interface::getInstance();
    interface.displayResumeMenu();
    // 1. Resume 2. new game 3. quit
    int choice = interface.getUserInput({1, 2, 3});
    switch (choice) {
        case 1: {
            // TODO make sure it resumes the game
            Game game('U', startDatabase.difficulty);
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



bool mainMenu(Database &startDatabase) {
    // returns false if user wants to quit the game
    if (startDatabase.canBeResumed) {
        return resumeMenu(startDatabase);
    } else {
        return newGameMenu(startDatabase);
    }
}


int main() {
    Database& startDatabase = Database::getInstance();
    while (mainMenu(startDatabase));
}