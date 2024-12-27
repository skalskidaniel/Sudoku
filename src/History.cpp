//
// Created by Wiktor on 27/12/2024.
//

#include "Sudoku/include/History.h"

void History::undo(Board board) {
    board = previous;
    previous = board;
}