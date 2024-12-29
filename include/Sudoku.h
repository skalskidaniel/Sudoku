//
// Created by Daniel Skalski on 28/12/2024.
//

#ifndef SUDOKU_H
#define SUDOKU_H
#include <Board.h>
#include <Database.h>
#include <Player.h>
#include <Manager.h>

//TODO class player is abstract error

class Sudoku {
public:
    Board board;

    Player player;

    Manager manager;

    enum Mode { SOLVER = 'S', USER = 'U' };
    enum Difficulty {EASY = 1, MEDIUM = 2, HARD = 3};

    Sudoku(const Mode &m, const Difficulty &d, const std::vector<Board> &savedBoards);

    void chooseBoard(const std::vector<Board> &savedBoards);

};



#endif //SUDOKU_H
