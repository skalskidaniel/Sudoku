#include <game.h>
#include <iostream>

bool newGameMenu(Database &db) {
    Interface& interface = Interface::getInstance();
    interface.displayMainMenu(db.bestScore);
    int choice = interface.getUserInputInt({1, 2});
    switch (choice) {
        case 1: {
            interface.displayModeSelection();
            int mode = interface.getUserInputInt({1, 2});
            switch (mode) {
                case 1: {
                    interface.displayDifficultySelection();
                    int difficulty = interface.getUserInputInt({1, 2, 3});
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

bool resumeMenu(Database &db) {
    Interface& interface = Interface::getInstance();
    interface.displayResumeMenu();
    int choice = interface.getUserInputInt({1, 2, 3});
    switch (choice) {
        case 1: {
            Game game('U', db.difficulty);
            game.start();
            return true;
        }
        case 2: {
            db.clearCurrentState();
            return newGameMenu(db);
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



bool mainMenu(Database &db) {
    if (db.canBeResumed) {
        return resumeMenu(db);
    } else {
        return newGameMenu(db);
    }
}


int main() {
    Database& db = Database::getInstance();
    while (mainMenu(db)) {
        db.loadSavedState();
    }
}