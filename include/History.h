//
// Created by Wiktor on 27/12/2024.
//

#ifndef HISTORY_H
#define HISTORY_H

#include "Board.h"
#include <stack>
#include <stdexcept>

class History {
public:
    std::stack<Board> previousBoards;

    History();

    // returns previous board, necessary for Sudoku class to update current board state
    Board undo(Board &newPreviousBoard);

    bool canUndo();

    void update(Board &board);
};



#endif //HISTORY_H
