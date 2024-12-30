//
// Created by Wiktor on 27/12/2024.
//

#include "ErrorTracker.h"

ErrorTracker::ErrorTracker(int maxErrors) {
    this->maxErrors = maxErrors;
    currentErrors = 0;
    isGameOver = false;
}

bool ErrorTracker::validateMove(Board board, Board solution, char mode) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if (board.currentState[i][j] != '0' && board.currentState[i][j] != solution.currentState[i][j]) {
                currentErrors++;
            }
        }
    }
    if (currentErrors >= maxErrors) {
        isGameOver = true;
        return false;
    }
    return true;
}