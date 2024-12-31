//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef GAME_H
#define GAME_H
#include <Sudoku.h>
#include <Interface.h>


class Game {
public:
    Interface& interface;
    Sudoku sudoku;

    Game(char mode, int difficulty);

    void start();

    void playUserMode();

    void playSolverMode();
};



#endif //GAME_H
