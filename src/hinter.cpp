//
// Created by Wiktor on 27/12/2024.
//

#include "Sudoku/include/hinter.h"

void hinter::provideHint(Board board, Board solution) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j< 9; j++) {
            if (board.currentState[i][j] == 0) {
                board.currentState[i][j] = solution.currentState[i][j];
            }
        }
    }
}

