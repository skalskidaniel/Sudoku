//
// Created by Daniel Skalski on 28/12/2024.
//

#include <random>
#include <vector>
#include "Sudoku.h"
#include <Solver.h>
#include <User.h>
#include <Database.h>


Sudoku::Sudoku(const Mode &m, const Difficulty &d)
    : player(nullptr), manager(0) {
    mode = m;
    if (m == USER) {
        player = std::make_unique<User>();
    } else {
        player = std::make_unique<Solver>();
    }

    difficulty = d;
    Database& db = Database::getInstance();
    if (db.canBeResumed) {
        db.loadSavedState();
        board = db.currentBoard;
        boardID = db.currentBoardID;
        difficulty = static_cast<Difficulty>(db.difficulty);
    } else {
        chooseBoard();
    }
    if (difficulty == EASY) {
        manager = Manager(10);
    } else if (difficulty == MEDIUM) {
        manager = Manager(5);
    } else {
        manager = Manager(2);
    }
    manager.errorTracker.currentErrors = db.currentErrors;
}


void Sudoku::chooseBoard() {
    Database& db = Database::getInstance();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, db.totalBoards - 1);
    int randomIndex = dis(gen);
    db.loadChosenBoard(randomIndex);
    board = db.currentBoard;
    boardID = randomIndex;
}

