//
// Created by Wiktor on 27/12/2024.
//

#include <Hinter.h>

void Hinter::provideHint(Board &currentBoard) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j< 9; j++) {
            if (currentBoard.currentState[i][j] == '0') {
                currentBoard.currentState[i][j] = currentBoard.solvedState[i][j];
                return;
            }
        }
    }
}

