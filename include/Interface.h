//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef INTERFACE_H
#define INTERFACE_H
#include <Board.h>
#include <string>



class Interface {
public:
    void displayBoard( Board &b);

    enum Colour {GREEN, YELLOW, RED};
    void displayMessage(const std::string &message, const Colour &c);

    void displayMainMenu(const int &bestScore);

    void displayResumeMenu();

    void displayModeSelection();

    void displayDifficultySelection();

    void displayInGameOptions(const int &currentErorrs, const int &maxErrors);

    void displayInputAndSolveInfo();

    // make chill sound during the game
    void sound();
};



#endif //INTERFACE_H
