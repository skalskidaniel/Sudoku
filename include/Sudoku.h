//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef SUDOKU_H
#define SUDOKU_H
#include <Board.h>
#include <Database.h>
#include <Player.h>
#include <Manager.h>

class Sudoku {
public:
    Board board;
    int boardID;
    std::unique_ptr<Player> player;
    Manager manager;

    enum Mode { SOLVER = 'S', USER = 'U' };
    enum Difficulty {EASY = 1, MEDIUM = 2, HARD = 3};
    Difficulty difficulty;
    Mode mode;

    Sudoku(const Mode &m, const Difficulty &d);

    void chooseBoard();

};



#endif //SUDOKU_H
