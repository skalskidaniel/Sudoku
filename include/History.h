//
// Created by Wiktor on 27/12/2024.
//

#ifndef HISTORY_H
#define HISTORY_H
#include "Board.h"

class History {
public:
    Board previousBoard;

    History();

    // returns previous board, necessary for Sudoku class to update current board state
    Board undo(Board &board);
};



#endif //HISTORY_H
