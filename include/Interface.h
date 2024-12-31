//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef INTERFACE_H
#define INTERFACE_H
#include <Board.h>
#include <string>
#include <iostream>

class Interface {
public:
    static Interface& getInstance() {
        static Interface instance;
        return instance;
    }

    void displayBoard(Board &b);
    enum Colour {GREEN, YELLOW, RED};
    void displayMessage(const std::string &message, const Colour &c);
    void displayMainMenu(const int &bestScore);
    void displayResumeMenu();
    void displayModeSelection();
    void displayDifficultySelection();
    void displayInGameOptions(const int &currentErrors, const int &maxErrors);
    void displayInputAndSolveInfo();
    int getUserInputInt(const std::vector<int> &availableValues);
    char getUserInputChar(const std::vector<char> &availableValues);

private:
    Interface() = default;
    ~Interface() = default;
    Interface(const Interface&) = delete;
    Interface& operator=(const Interface&) = delete;
};



#endif //INTERFACE_H
