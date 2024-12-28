//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef INTERFACE_H
#define INTERFACE_H
#include <Board.h>
#include <string>



class Interface {
    char mode;

    Interface(char mode);

    void displayBoard(const Board &b);

    void displayMessage(const std::string &message);

    std::string getUserInput();

    // make chill sound during the game
    void sound();
};



#endif //INTERFACE_H
