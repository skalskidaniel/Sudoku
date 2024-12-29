//
// Created by Daniel Skalski on 28/12/2024.
//

#include <random>
#include <vector>
#include "Sudoku.h"
#include <Solver.h>
#include <User.h>

//TODO class player and manager is not initialized in the constructor error

Sudoku::Sudoku (const Mode &m, const Difficulty &d, const std::vector<Board> &savedBoards) {
    if (m == USER) {
        player = User();
    } else {
        player = Solver();
    }

    if (d == EASY) {
        manager = Manager(10);
    } else if (d == MEDIUM) {
        manager = Manager(5);
    } else {
        manager = Manager(2);
    }
    chooseBoard(savedBoards);
}

void Sudoku::chooseBoard(const std::vector<Board> &savedBoards) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, savedBoards.size() - 1);
    int randomIndex = dis(gen);
    board = savedBoards[randomIndex];
}

