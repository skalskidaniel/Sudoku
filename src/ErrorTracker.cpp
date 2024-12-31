//
// Created by Wiktor on 27/12/2024.
//

#include "ErrorTracker.h"

ErrorTracker::ErrorTracker(int maxErrors) {
    this->maxErrors = maxErrors;
    currentErrors = 0;
    isGameOver = false;
}

bool ErrorTracker::validateMove(Board board, std::pair<std::pair<int, int>, char> move) {
    // TODO dodac sprawdzanie, czy aby na pewno user nie wybral juz wypelnionego pola, sprawdzic czy na pewno dobrze sprawdza poprawnosc
    bool is_valid = true;
    if(board.solvedState[move.first.first][move.first.second] != move.second) {
        ++currentErrors;
        is_valid = false;
    }

    if (!is_valid && currentErrors > maxErrors) {
        isGameOver = true;
        return false;
    }
    return is_valid;
}