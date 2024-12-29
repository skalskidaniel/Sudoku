//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef GAME_H
#define GAME_H
#include <Sudoku.h>
#include <Interface.h>
#include <iostream>



class Game {
public:
    Sudoku sudoku;

    Interface interface;

    Database database;

    Game(char mode, int difficulty);

    void start();

    void saveProgress();
};



#endif //GAME_H
