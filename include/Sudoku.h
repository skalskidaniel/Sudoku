//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef SUDOKU_H
#define SUDOKU_H
#include <Board.h>
#include <Player.h>
#include <Manager.h>


class Sudoku {
public:
    Board board;

    Player player;

    enum Mode { SOLVER = 'S', USER = 'U' };

    char mode;

    Manager manager;

    enum Difficulty {EASY = 1, MEDIUM = 2, HARD = 3};

    // default game starts with a user playing
    // TODO
    Sudoku(const Player &p, Mode m = USER, Difficulty d);

    void chooseBoard();
};



#endif //SUDOKU_H
