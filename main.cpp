#include <game.h>
#include <iostream>

int main() {
    Interface startInterface = Interface();
    Database startDatabase(false);

    if (startDatabase.canBeResumed) {
        startInterface.displayResumeMenu();

        int resumeChoice;
        while (true) {
            std::cin >> resumeChoice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter 1 to resume the game, 2 to start a new game, or 3 to quit." << std::endl;
            } else if (resumeChoice != 1 && resumeChoice != 2 && resumeChoice != 3) {
                std::cout << "Invalid input! Please enter 1 to resume the game, 2 to start a new game, or 3 to quit." << std::endl;
            } else {
                break;
            }
        }

        if (resumeChoice == 3) {
            std::cout << "Hope to see you soon!\n";
            return 0;
        } else if (resumeChoice == 1) {
            // Resume the game, resumed game is always in user mode
            Game g = Game('U', startDatabase.difficulty);
            g.sudoku.board = startDatabase.currentBoard;
            g.start();
        } else if (resumeChoice == 2) {
            // Start a new game
            startInterface.displayModeSelection();

            int modeChoice;
            while (true) {
                std::cin >> modeChoice;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input! Please choose valid game mode." << std::endl;
                } else if (modeChoice != 1 && modeChoice != 2) {
                    std::cout << "Invalid input! Please choose valid game mode." << std::endl;
                } else {
                    break;
                }
            }

            if (modeChoice == 1) {
                // User mode
                startInterface.displayDifficultySelection();

                int difficultyChoice;
                while (true) {
                    std::cin >> difficultyChoice;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input! Please choose a valid difficulty level." << std::endl;
                    } else if (difficultyChoice != 1 && difficultyChoice != 2 && difficultyChoice != 3) {
                        std::cout << "Invalid input! Please choose a valid difficulty level." << std::endl;
                    } else {
                        break;
                    }
                }

                if (difficultyChoice == 1) {
                    // EASY
                    Game g = Game('U', 1);
                    g.start();
                } else if (difficultyChoice == 2) {
                    // MEDIUM
                    Game g = Game('U', 2);
                    g.start();
                } else if (difficultyChoice == 3) {
                    // HARD
                    Game g = Game('U', 3);
                    g.start();
                } else {
                    throw std::runtime_error("Unknown difficulty!\n");
                }

            } else if (modeChoice == 2) {
                // Solver mode
                Game g = Game('S', 1);
                g.start();
            }
        }
    } else {
        startInterface.displayMainMenu(startDatabase.bestScore);

        int mainChoice;
        while (true) {
            std::cin >> mainChoice;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter 1 to start a game or 2 to quit." << std::endl;
            } else if (mainChoice != 1 && mainChoice != 2) {
                std::cout << "Invalid input! Please enter 1 to start a game or 2 to quit." << std::endl;
            } else {
                break;
            }
        }

        if (mainChoice == 2) {
            std::cout << "Hope to see you soon!\n";
            return 0;
        } else {
            // Start a new game
            startInterface.displayModeSelection();

            int modeChoice;
            while (true) {
                std::cin >> modeChoice;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid input! Please choose valid game mode." << std::endl;
                } else if (modeChoice != 1 && modeChoice != 2) {
                    std::cout << "Invalid input! Please choose valid game mode." << std::endl;
                } else {
                    break;
                }
            }

            if (modeChoice == 1) {
                // User mode
                startInterface.displayDifficultySelection();

                int difficultyChoice;
                while (true) {
                    std::cin >> difficultyChoice;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input! Please choose a valid difficulty level." << std::endl;
                    } else if (difficultyChoice != 1 && difficultyChoice != 2 && difficultyChoice != 3) {
                        std::cout << "Invalid input! Please choose a valid difficulty level." << std::endl;
                    } else {
                        break;
                    }
                }

                if (difficultyChoice == 1) {
                    // EASY
                    Game g = Game('U', 1);
                    g.start();
                } else if (difficultyChoice == 2) {
                    // MEDIUM
                    Game g = Game('U', 2);
                    g.start();
                } else if (difficultyChoice == 3) {
                    // HARD
                    Game g = Game('U', 3);
                    g.start();
                } else {
                    throw std::runtime_error("Unknown difficulty!\n");
                }

            } else if (modeChoice == 2) {
                // Solver mode
                Game g = Game('S', 1);
                g.start();
            }
        }
    }
    // TODO after all of this there will be again displayed main menu, consider making separate functions bo jest kurwa spaghetti powyzej

}
